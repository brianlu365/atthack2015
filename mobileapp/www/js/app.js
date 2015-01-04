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

// app.controller('weather', function ($scope) {
//   $http.get('https://query.yahooapis.com/v1/public/yql?q=select%20item.condition%20from%20weather.forecast%20where%20woeid%20%3D%202487889&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys').
//     success(function(data, status, headers, config) {
//       // this callback will be called asynchronously
//       // when the response is available
//       console.log(data)
//       $scope.weather = data;
      
//     }).
//     error(function(data, status, headers, config) {
//       // called asynchronously if an error occurs
//       // or server returns response with an error status.
//     });
// });
// $.ajax({
//   url:'https://query.yahooapis.com/v1/public/yql?q=select%20item.condition%20from%20weather.forecast%20where%20woeid%20%3D%202487889&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys',
//   success: function(result) {
//     $('.temp').text() = result.stringify()
//   }
// });
