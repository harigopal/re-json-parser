[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

let str = ReasonReact.stringToElement;

Rdp.execute();

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (str(message)) </h2>
      </div>
      <p className="App-intro">
        (str("To get started, edit"))
        <code> (str(" src/app.re ")) </code>
        (str("and save to reload."))
      </p>
    </div>,
};