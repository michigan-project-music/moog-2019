import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';

import firebase from 'firebase/app';
import 'firebase/database'; // If using Firebase database
import 'firebase/storage';  // If using Firebase storage

const config = {
apiKey: "AIzaSyDBFJtzxQgl3JkPKwOJCVCQEsqnp16J5OM",
    authDomain: "test-playground-b36c0.firebaseapp.com",
    databaseURL: "https://test-playground-b36c0.firebaseio.com",
    projectId: "test-playground-b36c0",
    storageBucket: "test-playground-b36c0.appspot.com",
    messagingSenderId: "103494638490"
};




class App extends Component {

  updateState() {
      console.log("woww");
      var database = firebase.database();

      firebase.database().ref('andrew').set({

        name: "kiran",
        othername: "kirdant"

      })



   }

    sendKeyVal() {
      console.log("woww");

      var database = firebase.database();

      var key = document.getElementById("KEY").value;
      var val = parseInt(document.getElementById("VALUE").value);


      firebase.database().ref(key).set({

        value: val

      })
   


   }

  render() {

    firebase.initializeApp(config)


    return (
      <div className="App">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <p>
            Edit <code>src/App.js</code> and save to reload.
          </p>
          <a
            className="App-link"
            href="https://reactjs.org"
            target="_blank"
            rel="noopener noreferrer"
          >
          </a>

          <button  onClick = {this.updateState}> Click 1</button>
          <input defaultValue="key" id = "KEY"/> 
          <input type="number" defaultValue = "0" id = "VALUE"/> 

          <button onClick = {this.sendKeyVal}> Send Key/Num Pair</button>
          <button> Click 3</button>

          <p>Text 1</p>
          <p>Text 2</p>
          <p>Text 5</p>


        </header>
      </div>
    );
  }
}

export default App;
