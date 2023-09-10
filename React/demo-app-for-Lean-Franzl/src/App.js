import "./App.css";
import data from "./data/username.csv";
import * as d3 from "d3";
import { useState } from "react";

var firstnames = [];
var lastnames = [];

function App() {
  // let filename = "./data/username";

  var [count, setCount] = useState(0);

  d3.csv(data).then((loadedData) => {
    for (let i = 0; i < 3; i++) {
      firstnames.push(loadedData[i].First_name);
      lastnames.push(loadedData[i].Last_name);
    }
    console.log("first time", firstnames, lastnames);
  });

  console.log("second time", firstnames, lastnames);

  return (
    <div className="App">
      <header className="App-header">
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <button
          style={{ width: "80px", height: "40px" }}
          onClick={() => setCount(count + 1)}
        >
          Press me!
        </button>
        <p>Count: {count}</p>
        <p>the content of the list: {firstnames[0]}</p>
        Learn React
      </header>
    </div>
  );
}

export default App;
