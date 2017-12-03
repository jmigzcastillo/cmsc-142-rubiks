$(function() {
  // hard coded pa ito lol
  $("#inputField").val("WRY\nBWY\nBWR\nGRR\nGRR\nGGW\nYBG\nYBY\nRRO\nYOO\nBOO\nBWB\nBWO\nBGO\nRWO\nGGW\nYYG\nYOW");

  var determineColor = function(c) {
    switch(c) {
      case 'W':
          return "whiteColor";
      case 'R':
          return "redColor";
      case 'B':
          return "blueColor";
      case 'O':
          return "orangeColor";
      case 'G':
          return "greenColor";
      case 'Y':
          return "yellowColor";
    }
  }

  $("#submitButton").click(function(event) {
    var row = 0;
    var face = 0;
    var count = 0;
    inputCube = $("#inputField").val().split("\n");

    while(count < 18) {
      $("#"+face+""+row+"0").addClass(determineColor(inputCube[count].charAt(0)));
      $("#"+face+""+row+"1").addClass(determineColor(inputCube[count].charAt(1)));
      $("#"+face+""+row+"2").addClass(determineColor(inputCube[count].charAt(2)));
      row++;
      row = row % 3;
      count++;
      if(count % 3 == 0) face++;
    }

    $("#magic").css({display: 'block'});

    // var Cube = $("#CubeField").val();
    //send to server to solve
    //response is the solution (array of strings)
    var data = {
      Cube: $("#CubeField").val()
    }

    $.ajax({
      type: "POST",
      url: "/solvecube",
      data: data,
      success: function(data) {
        console.log(data);
      }
    });
  });

  // For the animation effects
  // Reference: https://paulrhayes.com/animated-css3-cube-interface-using-3d-transforms/
  var props = 'transform WebkitTransform MozTransform OTransform msTransform'.split(' '),
  prop,
  el = document.createElement('div');

  for(var i = 0, l = props.length; i < l; i++) {
    if(typeof el.style[props[i]] !== "undefined") {
        prop = props[i];
        break;
    }
  }

  var xAngle = 0, yAngle = 0;
  document.addEventListener('keydown', function(e) {
    switch(e.keyCode) {
      case 37: // left
        yAngle -= 90;
        break;
      case 38: // up
        xAngle += 90;
        break;
      case 39: // right
        yAngle += 90;
        break;
      case 40: // down
        xAngle -= 90;
        break;
    };

    document.getElementById('cube').style[prop] = "rotateX("+xAngle+"deg) rotateY("+yAngle+"deg)";
  }, false);
});
