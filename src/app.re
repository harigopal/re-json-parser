[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

let str = ReasonReact.stringToElement;

Rdp.execute(Rdp.simpleString);

Rdp.execute(Rdp.simpleJson);

Rdp.execute(Rdp.multipleJson);

Rdp.execute(Rdp.nestedJson);

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (str(message)) </h2>
      </div>
      <p className="App-intro">
        (
          str(
            "Check the console to see output from the recursive descent parser.",
          )
        )
      </p>
    </div>,
};