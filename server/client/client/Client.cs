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

		public void SayHello()
		{
			HelloRequest.Builder tmp = HelloRequest.CreateBuilder ();
			tmp.SetName ("NGUYEN Hong San");
			HelloRequest req = tmp.BuildPartial();
			MemoryStream stream = new MemoryStream ();
			req.WriteTo(stream);
			byte[] data1 = stream.ToArray();
			byte[] data2 = Post((int)Service.HELLO, data1);
			HelloReply rep  = HelloReply.CreateBuilder().MergeFrom(data2).BuildPartial();
			Console.WriteLine (rep.Text);
		}

		public Session CreateSession()
		{
			CreateSessionRequest.Builder tmp = CreateSessionRequest.CreateBuilder ();
			var ran = new Random ();
			tmp.SetName ("Session" + ran.Next(1000));
			tmp.SetToken (token);
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
				return ret;
			}

			/* TODO: join session here */
			return null;
		}

		public Session JoinSession(string sid, string host, int port)
		{
			Session ret = new Session (sid);
			ret.Open (host, port);
			/* TODO: join session here */

			return ret;
		}

		public static void Main (string[] args)
		{
			Client c = new Client ();
			c.SayHello();
			//Session session = c.CreateSession("127.0.0.1", 5678);
			Session session = c.CreateSession();
			if (session != null) 
			{
				session.PingPong ();
			}
		}
	}
}
