using System;
using System.Net;
using System.IO;
using System.Text;
using System.Net.Sockets;
using System.Threading;

namespace Ocean
{
	class Client
	{
		Session session;
		public Client(string host, int port)
		{
			session = new Session (host, port);
		}

		public void Close()
		{
			if (session.IsOpened ()) session.Close ();
		}
		public Session Session()
		{
			return session;
		}
		public string SendHttpRequest(int type, string message)
		{
			string url = "http://127.0.0.1:8088/ocean/r/" + type;
			var request = System.Net.HttpWebRequest.Create(url);
			request.Method ="POST";
			request.ContentType = "application/json";
			var requestStream = request.GetRequestStream();
			byte[] bytes = Encoding.UTF8.GetBytes(message);
			requestStream.Write(bytes, 0, bytes.Length);
			requestStream.Close ();

			HttpWebResponse response = (HttpWebResponse)request.GetResponse ();
			Stream receiveStream = response.GetResponseStream();
			StreamReader reader = new StreamReader(receiveStream);
			string text = reader.ReadToEnd ();
			return text;
		}

		public void SayHello()
		{
			string text = SendHttpRequest (1, "{\"text\":\"NGUYEN Hong San\"}");
			Console.WriteLine (text);
		}

		public static void Main (string[] args)
		{
			Client c = new Client ("127.0.0.1", 5678);
			c.SayHello();
			Session s = c.Session ();
			s.Open ();
			s.PingPong ();
			c.Close ();
		}
	}
}
