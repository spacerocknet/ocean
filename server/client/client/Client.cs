using System;
using System.Net;
using System.IO;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using comm;

namespace Ocean
{
	class Client
	{
		public string token = "12345678";
		public byte[] Post(int type, byte[] data)
		{
			string url = "http://127.0.0.1:8088/ocean/r/" + type;
			var request = System.Net.HttpWebRequest.Create(url);
			request.Method ="POST";
			request.ContentType = "application/json";
			var requestStream = request.GetRequestStream();
			requestStream.Write(data, 0, data.Length);
			requestStream.Close ();

			HttpWebResponse response = (HttpWebResponse)request.GetResponse ();

			Stream receiveStream = response.GetResponseStream();

			using (MemoryStream ms = new MemoryStream())
			{
				receiveStream.CopyTo(ms);
				return ms.ToArray();
			}
		}

		public bool Signin(string uid, string password)
		{
			SigninRequest.Builder tmp = SigninRequest.CreateBuilder ();
			tmp.SetUid (uid);
			tmp.SetPassword(password);
			SigninRequest req = tmp.BuildPartial();
			MemoryStream stream = new MemoryStream ();
			req.WriteTo(stream);
			byte[] data1 = stream.ToArray();
			byte[] data2 = Post((int)comm.Service.CREATE_SESSION, data1);
			SigninReply rep  = SigninReply.CreateBuilder().MergeFrom(data2).BuildPartial();

			if (rep.Type == (int)Error.OK)
			{
				this.token = rep.Token;
				return true;
			}
			return false;

		}
		public Session CreateSession()
		{
			CreateSessionRequest.Builder tmp = CreateSessionRequest.CreateBuilder ();
			tmp.SetToken (token);
			tmp.SetGame ((int)Game.TICTACTOE);
			CreateSessionRequest req = tmp.BuildPartial();
			MemoryStream stream = new MemoryStream ();
			req.WriteTo(stream);
			byte[] data1 = stream.ToArray();
			byte[] data2 = Post((int)comm.Service.CREATE_SESSION, data1);
			CreateSessionReply rep  = CreateSessionReply.CreateBuilder().MergeFrom(data2).BuildPartial();

			if (rep.Type == (int)Error.OK)
			{
				Session ret = new Session (rep.Sid);
				ret.Open (rep.Host, rep.Port);
				if (ret.Join (this.token)) return ret;
			}
			return null;
		}

		public Session JoinSession(string sid, string host, int port)
		{
			Session ret = new Session (sid);
			ret.Open (host, port);
			if (ret.Join (this.token)) return ret;
			return null;
		}

		public static void Main (string[] args)
		{
			Client c = new Client ();
			Session session = c.CreateSession();
			if (session != null) 
			{
				Console.WriteLine ("Session created:"+ session.Id);
				Thread.Sleep (100);
				session.Close ();
			}
		}
	}
}
