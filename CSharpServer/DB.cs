using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
using System.Data;
using System.Data.SqlClient;

namespace CSharpServer
{

    /// <summary>
    /// 진짜 dbms에 쿼리날려버리는 클래스로, 가능한 조심해서 씁니다
    /// </summary>
    public class DB
    {
        public static string DataSource = "cdn.2dimensia.com";
        public static string DataBase = "elcid0";
        public static string UserID = "testserver";
        public static string Password = "testserverpassword1";


        public void TestConnection()
        {
            string MyConnectionString = "Data Source=" + DataSource + ";Database=" + DataBase + ";User Id=" + UserID + ";Password=" + Password + ";";

            MySqlConnection connection = new MySqlConnection(MyConnectionString);
            MySqlCommand cmd;
            connection.Open();
            try
            {
                cmd = connection.CreateCommand();
                cmd.CommandText = "select * from use_cards";
                Util.Log(connection.State.ToString());

                DataSet ds = new DataSet();
                MySqlDataAdapter da = new MySqlDataAdapter("select * from ref_cards", connection);

                da.Fill(ds);

                foreach (DataRow row in ds.Tables[0].Rows)
                {
                    Console.Write(string.Format("이름 : {0} \n", row["name"]));
                }
            }
            catch (System.Exception ex)
            {
                Util.Log(ex.Message);
            }

            finally
            {
                if (connection.State == System.Data.ConnectionState.Open)
                {
                    connection.Close();
                }
            }
        }


        public void TestQueryWithPooled()
        {
            // 최소 20 Connection 지정
            string MyConnectionString =
                "Server=" + DataSource + ";Database=" + DataBase + ";Uid=" + UserID + ";Pwd=" + Password + ";Min Pool Size=20;Pooling=true;Max Pool Size=100;Connection Timeout=15;";

            using (MySqlConnection connection = new MySqlConnection(MyConnectionString))
            using (MySqlDataAdapter da = new MySqlDataAdapter("select * from ref_cards", connection))
            {
                connection.Open();
                try
                {
                    //이걸로 쿼리 다날라감
                    DataSet ds = new DataSet();
                    da.Fill(ds);

                    foreach (DataRow row in ds.Tables[0].Rows)
                    {
                        Console.Write(string.Format("이름 : {0} \n", row["name"]));
                    }


                    if (ds.Tables.Count == 0)
                    {
                        //TODO : select결과가 없거나 select를 수반하지 않는 액션임
                    }

                }
                catch (System.Exception ex)
                {
                    Util.Log(ex.Message);
                }
                finally
                {
                    if (connection.State == System.Data.ConnectionState.Open)
                    {
                        connection.Close();
                    }
                }
            }
        }

        public void Refresh()
        {
            Util.Log("MySQL Refreshed");
        }

        public void Initialize(MySqlConnectionStringBuilder setting)
        {
            builder = setting;
        }
        public MySqlConnectionStringBuilder builder;

        public DB(MySqlConnectionStringBuilder setting)
        {
            Initialize(setting);
        }

        /// <summary>
        /// 다중 쿼리를 날리는 클래스
        /// </summary>
        public class Transaction
        {
            public Transaction(DB db)
            {
                initialize(database = db);
            }

            string MyConnectionString;
            List<string> MyQueryString = new List<string>();

            bool _succeeded = false;
            public bool Succeeded
            {
                get
                {
                    return _succeeded;
                }
            }

            DB database;
            public DataSet Result = new DataSet();

            /// <summary>
            /// 연결을 초기화한다.
            /// </summary>
            /// <param name="connector"></param>
            void initialize(DB db)
            {
                MyConnectionString = db.builder.ToString();
            }

            public void AddQuery(string str)
            {
                MyQueryString.Add(str);
            }

            public int CountOfQuery
            {
                get
                {
                    return MyQueryString.Count;
                }
            }

            public void Run()
            {
                using (MySqlConnection connection = new MySqlConnection(MyConnectionString))
                {
                    connection.Open();
                    MySqlCommand myCommand = new MySqlCommand();
                    myCommand.Connection = connection;
                    MySqlTransaction myTransac;
                    myTransac = connection.BeginTransaction(IsolationLevel.ReadCommitted);
                    myCommand.Transaction = myTransac;
                    string current_query = string.Empty;
                    try
                    {
                        foreach (var v in MyQueryString)
                        {
                            myCommand.CommandText = current_query = v;
                            myCommand.ExecuteNonQuery();
                        }
                        myTransac.Commit();

                        _succeeded = true;
                    }
                    catch (System.Exception ex)
                    {
                        _succeeded = false;
                        myTransac.Rollback();
                        Util.Log("ERROR : Query(" + current_query + ")" + ex.Message);
                    }
                    finally
                    {
                        if (connection.State == System.Data.ConnectionState.Open)
                        {
                            connection.Close();
                        }
                    }
                }
            }

            public void ToContainer(List<List<Dictionary<string, string>>> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        List<Dictionary<string, string>> a_table = new List<Dictionary<string, string>>();
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            Dictionary<string, string> a_row = new Dictionary<string, string>();
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                a_row.Add(cow.ToString(), row[cow].ToString());
                            }
                            a_table.Add(a_row);
                        }
                        target.Add(a_table);
                    }
                }
            }

            public void ToContainerFirstTable(List<Dictionary<string, string>> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            Dictionary<string, string> a_row = new Dictionary<string, string>();
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                a_row.Add(cow.ToString(), row[cow].ToString());
                            }
                            target.Add(a_row);
                        }
                        //first table만 놓는다.
                        return;
                    }
                }
            }

            public void ToContainerFirstTableFirstRow(Dictionary<string, string> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        List<Dictionary<string, string>> a_table = new List<Dictionary<string, string>>();
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                target.Add(cow.ToString(), row[cow].ToString());
                            }
                            //first table의 first row만 놓는다.
                            return;
                        }
                    }
                }
            }

            /// <summary>
            /// 테이블들/row들/각row의데이터 순으로 List/List/Dic
            /// </summary>
            /// <returns></returns>
            public List<List<Dictionary<string, string>>> ToContainer()
            {
                List<List<Dictionary<string, string>>> kv = new List<List<Dictionary<string, string>>>();
                ToContainer(kv);
                return kv;
            }

            public List<Dictionary<string, string>> ToContainerFirstTable()
            {
                List<Dictionary<string, string>> kv = new List<Dictionary<string, string>>();
                ToContainerFirstTable(kv);
                return kv;
            }

            public Dictionary<string, string> ToContainerFirstTableFirstRow()
            {
                Dictionary<string, string> kv = new Dictionary<string, string>();
                ToContainerFirstTableFirstRow(kv);
                return kv;
            }


            public override string ToString()
            {
                string res = "Query = ";
                foreach (var v in MyQueryString)
                {
                    res += "\n" + MyQueryString;
                }
                res += "\n";

                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            res += "{ ";
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                if (j != 0) res += ",";
                                res += "\"" + cow + "\":\"" + row[cow] + "\"";
                            }
                            res += "}\n";
                        }
                    }
                }
                else
                {
                    res += "No Result";
                }

                return res;
            }

        }

        /// <summary>
        /// 실제 1쿼리에 해당하는 클래스. 매번 재접속(물론 pooling되어있는)한다.
        /// </summary>
        public class Query
        {
            public string QueryString
            {
                get
                {
                    return MyQueryString;
                }
            }
            string MyConnectionString;
            string MyQueryString;

            bool _succeeded = false;
            public bool Succeeded
            {
                get
                {
                    return _succeeded;
                }
            }

            /// <summary>
            /// 연결을 초기화한다.
            /// </summary>
            /// <param name="connector"></param>
            void initialize(DB db)
            {
                MyConnectionString = db.builder.ToString();
            }

            public bool IsSucceededButNoResult
            {
                get
                {
                    return Succeeded && ToContainerFirstTableFirstRow().Count == 0;
                }
            }

            public bool IsSucceededAndHasResult
            {
                get
                {
                    return Succeeded && ToContainerFirstTableFirstRow().Count != 0;
                }
            }

            /// <summary>
            /// 쿼리를 생성만 하면 자동으로 날라간다.
            /// </summary>
            /// <param name="connector"></param>
            /// <param name="query"></param>
            public Query(DB connector, string query)
            {
                initialize(connector);
                Result.Clear();
                launchQueryWithPooled(MyQueryString = query);
            }

            public DataSet Result = new DataSet();

            //             DataSet ds = new DataSet();
            //                     da.Fill(ds);
            // 
            //                     foreach (DataRow row in ds.Tables[0].Rows)
            //                     {
            //                         Console.Write(string.Format("이름 : {0} \n", row["name"]));
            //                     }

            public void ToContainerAutoValue(List<List<Dictionary<string, Meta.AutoValue>>> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        List<Dictionary<string, Meta.AutoValue>> a_table = new List<Dictionary<string, Meta.AutoValue>>();
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            Dictionary<string, Meta.AutoValue> a_row = new Dictionary<string, Meta.AutoValue>();
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                a_row.Add(cow.ToString(), new Meta.AutoValue(row[cow].ToString()));
                            }
                            a_table.Add(a_row);
                        }
                        target.Add(a_table);
                    }
                }
            }

            public void ToContainerFirstTableAutoValue(List<Dictionary<string, Meta.AutoValue>> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            Dictionary<string, Meta.AutoValue> a_row = new Dictionary<string, Meta.AutoValue>();
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                a_row.Add(cow.ToString(), new Meta.AutoValue(row[cow].ToString()));
                            }
                            target.Add(a_row);
                        }
                        //first table만 놓는다.
                        return;
                    }
                }
            }

            public void ToContainerFirstTableFirstRowAutoValue(Dictionary<string, Meta.AutoValue> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        List<Dictionary<string, Meta.AutoValue>> a_table = new List<Dictionary<string, Meta.AutoValue>>();
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                target.Add(cow.ToString(), new Meta.AutoValue(row[cow].ToString()));
                            }
                            //first table의 first row만 놓는다.
                            return;
                        }
                    }
                }
            }

            public void ToContainer(List<List<Dictionary<string, string>>> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        List<Dictionary<string, string>> a_table = new List<Dictionary<string, string>>();
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            Dictionary<string, string> a_row = new Dictionary<string, string>();
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                a_row.Add(cow.ToString(), row[cow].ToString());
                            }
                            a_table.Add(a_row);
                        }
                        target.Add(a_table);
                    }
                }
            }

            public void ToContainerFirstTable(List<Dictionary<string, string>> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            Dictionary<string, string> a_row = new Dictionary<string, string>();
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                a_row.Add(cow.ToString(), row[cow].ToString());
                            }
                            target.Add(a_row);
                        }
                        //first table만 놓는다.
                        return;
                    }
                }
            }

            public void ToContainerFirstTableFirstRow(Dictionary<string, string> target)
            {
                target.Clear();
                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        List<Dictionary<string, string>> a_table = new List<Dictionary<string, string>>();
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                target.Add(cow.ToString(), row[cow].ToString());
                            }
                            //first table의 first row만 놓는다.
                            return;
                        }
                    }
                }
            }

            /// <summary>
            /// 테이블들/row들/각row의데이터 순으로 List/List/Dic
            /// </summary>
            /// <returns></returns>
            public List<List<Dictionary<string, string>>> ToContainer()
            {
                List<List<Dictionary<string, string>>> kv = new List<List<Dictionary<string, string>>>();
                ToContainer(kv);
                return kv;
            }

            public List<Dictionary<string, string>> ToContainerFirstTable()
            {
                List<Dictionary<string, string>> kv = new List<Dictionary<string, string>>();
                ToContainerFirstTable(kv);
                return kv;
            }

            public Dictionary<string, string> ToContainerFirstTableFirstRow()
            {
                Dictionary<string, string> kv = new Dictionary<string, string>();
                ToContainerFirstTableFirstRow(kv);
                return kv;
            }

            /// <summary>
            /// 테이블들/row들/각row의데이터 순으로 List/List/Dic
            /// </summary>
            /// <returns></returns>
            public List<List<Dictionary<string, Meta.AutoValue>>> ToContainerAutoValue()
            {
                List<List<Dictionary<string, Meta.AutoValue>>> kv = new List<List<Dictionary<string, Meta.AutoValue>>>();
                ToContainerAutoValue(kv);
                return kv;
            }

            public List<Dictionary<string, Meta.AutoValue>> ToContainerFirstTableAutoValue()
            {
                List<Dictionary<string, Meta.AutoValue>> kv = new List<Dictionary<string, Meta.AutoValue>>();
                ToContainerFirstTableAutoValue(kv);
                return kv;
            }

            public Dictionary<string, Meta.AutoValue> ToContainerFirstTableFirstRowAutoValue()
            {
                Dictionary<string, Meta.AutoValue> kv = new Dictionary<string, Meta.AutoValue>();
                ToContainerFirstTableFirstRowAutoValue(kv);
                return kv;
            }


            public override string ToString()
            {
                string res = "Query = " + MyQueryString + "\n";

                if (Result.Tables.Count != 0)
                {
                    for (int i = 0; i < Result.Tables.Count; ++i)
                    {
                        foreach (DataRow row in Result.Tables[i].Rows)
                        {
                            res += "{ ";
                            for (int j = 0; j < Result.Tables[i].Columns.Count; ++j)
                            {
                                DataColumn cow = Result.Tables[i].Columns[j];
                                if (j != 0) res += ",";
                                res += "\"" + cow + "\":\"" + row[cow] + "\"";
                            }
                            res += "}\n";
                        }
                    }
                }
                else
                {
                    res += "No Result";
                }

                return res;
            }

            void launchQueryWithPooled(string query)
            {
                _succeeded = true;
                START:
                using (MySqlConnection connection = new MySqlConnection(MyConnectionString))
                using (MySqlDataAdapter da = new MySqlDataAdapter(query, connection))
                {


                    try
                    {
                        connection.Open();
                        //async 는 어차피 동기로 동작하도록 로직이 되있는데다가 exception throw 도 하지 않기 때문에 안쓴다.
                        //                         IAsyncResult asResult = da.FillAsync(Result);
                        //                         while (!asResult.IsCompleted)
                        //                         {
                        //                             Util.Log("Wait for Query Finish...");
                        //                         }

                        int affected_row = da.Fill(Result);
                        //Util.Log("affected_row = " + affected_row);

                        //Util.Log("Query Finished");

                        if (Result.Tables.Count == 0)
                        {
                            //TODO : select가 없거나, select 결과값이 0인경우

                        }
                    }
                    catch (System.TimeoutException t_ex)
                    {
                        Util.Log(t_ex);
                        Util.Log("Reconnect");
                        goto START;
                    }
                    catch (MySql.Data.MySqlClient.MySqlException m_ex)
                    {
                        Util.Log(m_ex);
                        if (m_ex.ErrorCode == 2006 || m_ex.Message == "Timeout Expired")
                        {
                            Util.Log("Reconnect");
                            goto START;
                        }
                    }
                    catch (System.Exception ex)
                    {
                        _succeeded = false;
                        Util.Log("ERROR : Query[" + query + "]\n" + ex.ToString());
                    }
                    finally
                    {
                        if (connection.State == System.Data.ConnectionState.Open)
                        {
                            connection.Close();
                        }
                    }
                }
            }

        }

    }
}
