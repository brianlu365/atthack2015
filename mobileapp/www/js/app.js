// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
angular.module('starter', ['ionic'])
run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {
    // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
    // for form inputs)
    if(window.cordova && window.cordova.plugins.Keyboard) {
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);
    }
    
    if(window.StatusBar) {
      StatusBar.styleDefault();
    }


  });
})

var shirtIndex = 0;
var pantsIndex = 0;

function selectClothes(){
  console.log("hi")
  var m2x = new M2X("f68404a95d271e5d81c4d7f9224cbd8d");
  var date = new Date();
  m2x.devices.postMultiple('bb84147dbab191356d0b5fb090c19a9e', 
    {
      "shirtposition": [{ "timestamp": date.toISOString(), "value": 3 }],
      "pantsposition": [{ "timestamp": date.toISOString(), "value": 4 }]
    })
}
