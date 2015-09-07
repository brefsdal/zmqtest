package zmqtest

import java.nio.charset.Charset
import org.zeromq.ZMQ

/**
 * Created by brianrefsdal on 9/6/15.
 */
object Subscriber {
  def main (args: Array[String]) {
    val ctx = ZMQ.context(1)
    val subscriber = ctx.socket(ZMQ.SUB)
    subscriber.connect("tcp://localhost:9000")
    // Important. Set the subscribe filter.
    subscriber.subscribe(Array.empty)
    0 until 100 foreach { ii =>
      val str = subscriber.recvStr(Charset.forName("UTF-8")).trim()
      println(str)
    }
    subscriber.close()
    ctx.term()
  }
}
