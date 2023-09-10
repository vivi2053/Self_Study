import logo from './logo.svg';
import './App.css';
import Unity , { UnityContext } from 'react-unity-webgl';

const _unityContext = new UnityContext({
  loaderUrl: "build/2d_single_scene.loader.js",
  dataUrl: "build/2d_single_scene.data",
  frameworkUrl: "build/2d_single_scene.framework.js",
  codeUrl: "build/2d_single_scene.wasm",
});

function App() {
  return (
<Unity className="unity" unityContext={_unityContext}/>);
}

export default App;
