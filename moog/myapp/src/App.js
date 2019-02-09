import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';

import firebase from 'firebase';


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

      firebase.database().ref('string').set({

        name: "kiran",
        othername: "kirant"

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
          <button> Click 2</button>
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
