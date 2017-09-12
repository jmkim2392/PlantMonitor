#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

var plotly = require('plotly')('jmkim2392','v6w5xlbx9j');
var five = require("johnny-five");
var board = new five.Board();

// plotly init data
var data = [{x:[], y:[], mode: "markers", stream:{token:'25tm9197rz', maxpoints:20}}];
var layout = {fileopt : "overwrite", filename : "photoresistor nodey arduino!"};

// lets do this
board.on("ready", function() {
  // create a new `photoresistor` sensor object
  var photoresistor = new five.Sensor({
    pin: "A0",
    freq: 1000 // send reading every 1000ms
  });
  // initialize that plotly graph
  plotly.plot(data,layout,function (err, res) {
    if (err) console.log(err);
    console.log(res);
    //once it's initialized, create a plotly stream
    //to pipe your data!
    var stream = plotly.stream('25tm9197rz', function (err, res) {
      if (err) console.log(err);
      console.log(res);
    });
    // this gets called every time photoresistor returns its value
    photoresistor.scale([ 0, 200 ]).on("data", function() {
      data = {
        x : getDateString(),
        y : 0,
        marker : {
          size : this.value
        }
      };
      // write the data to the plotly stream
      stream.write(JSON.stringify(data)+'\n');
    });
  });
});

// little helper function to get a nicely formatted date string
function getDateString () {
  var time = new Date();
  // 14400000 is (GMT-4 Montreal)
  // for your timezone just multiply +/-GMT by 3600000
  var datestr = new Date(time - 14400000).toISOString().replace(/T/, ' ').replace(/Z/, '');
  return datestr;
}

