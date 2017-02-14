using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpServer
{
    public class SenderRequestedDuelMatching
    {
        public class Parameters
        {
            public int duelid;
            public Nettention.Proud.HostID firstHostID;
            public Nettention.Proud.HostID secondHostID;
            public string firstplayerid = "none";
            public string secondplayerid = "none";
            public string team1Serialized;
            public string team2Serialized;
            public bool succeeded;
            public bool p1IsBot;
            public bool p2IsBot;
            public int p1WinEstimatedRate = 0;
            public int p2WinEstimatedRate = 0;
            public int p1LoseEstimatedRate = 0;
            public int p2LoseEstimatedRate = 0;
            public int p1CurrentScore = 0;
            public int p2CurrentScore = 0;
        }
    }
}
