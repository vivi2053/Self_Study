import React, { useEffect, useState } from "react";
import Unity, { UnityContext } from "react-unity-webgl";

const UnityView = () => {
  const unityContext = new UnityContext({
    loaderUrl: "build/build_1018.loader.js",
    dataUrl: "build/build_1018.data",
    frameworkUrl: "build/build_1018.framework.js",
    codeUrl: "build/build_1018.wasm",
  });

  var [displayVal, setDisplayVal] = useState("");
  unityContext.on("quitted", () => {
    console.log("Game quit");
  });

  unityContext.on("loaded", () => {
    console.log("Game loaded");
  });

  unityContext.on("progress", (progression) => {
    console.log("Game loading", progression);
  });

  unityContext.on("error", (message) => {
    console.log("Game errored", message);
  });

  useEffect(() => {
    unityContext.on("OutputMessage", (message) => {
      console.log("OutputMessage", message);
      setDisplayVal(message);
    });
  }, []);

  const handleClick = () => {
    console.log("Button pressed to invoke unity");
    unityContext.send("ReactReceive", "PaintPlayer", "blue");
  };

  return (
    <div>
      <p>Value received from Unity is: {displayVal}</p>
      <p>
        The button below invokes the method "SpawnEnemies" in "GameController"
        with argument "yes".
      </p>
      <div style={{ margin: "0 auto" }}>
        <button style={{ marginBottom: "20px" }} onClick={handleClick}>
          Invoke Unity
        </button>
      </div>
      <Unity
        unityContext={unityContext}
        style={{ width: "90%", height: "90%" }}
      />
    </div>
  );
};
export default UnityView;
