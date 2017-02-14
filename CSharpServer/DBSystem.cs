using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace CSharpServer
{
    public class DBSystem
    {
        public static DBSystem Instance
        {
            get
            {
                if(_instance == null)
                {
                    _instance = new DBSystem();
                }
                return _instance;
            }
        }

        static DBSystem _instance;

        public static DB database;
        public void Initialize()
        {
            MySql.Data.MySqlClient.MySqlConnectionStringBuilder builder = new MySql.Data.MySqlClient.MySqlConnectionStringBuilder();
            builder.Server = DB.DataSource;
            builder.Database = DB.DataBase;
            builder.UserID = DB.UserID;
            builder.Password = DB.Password;
            builder.AllowZeroDateTime = true;
            builder.MinimumPoolSize = 20;
            builder.MaximumPoolSize = 20;
            builder.AllowUserVariables = true;
            builder.Pooling = true;
            builder.ConnectionTimeout = 15;
            database = new DB(builder);
            Util.Log("DB Location :" + DB.DataSource);
            Util.Log("DB :" + DB.DataBase);
            Util.Log("ID :" + DB.UserID);
        }

        private DBSystem() { }
    }
}
