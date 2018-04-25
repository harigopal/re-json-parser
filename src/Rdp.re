type pair = (string, value)
and value =
  | Object_(object_)
  | String_(string)
and object_ =
  | EmptyObject
  | ObjectWithMembers(members)
and members =
  | Pair(pair)
  | PairAndMembers(pair, members);

let myJson = "{\"hello\": \"world\"}";

let myString = "\"hello\"";

let explode = (s: string) : list(char) => {
  let rec aux = (str: string) =>
    switch (str) {
    | "" => []
    | str =>
      let head = str.[0];
      let tail = String.sub(str, 1, String.length(str) - 1);
      [head, ...aux(tail)];
    };
  aux(s);
};

let implode = (l: list(char)) : string => {
  let rec aux = (acc, l) =>
    switch (l) {
    | [] => acc
    | [h, ...t] => aux(acc ++ String.make(1, h), t)
    };
  aux("", l);
};

let parseString = json => {
  let rec aux = (sublist, json) =>
    switch (json) {
    | [] => []
    | [h, ...t] => h == '"' ? sublist : aux([h, ...sublist], t)
    };
  let s = aux([], json) |> List.rev |> implode;
  String_(s);
};

let parseValue = json =>
  switch (json) {
  | [] => None
  | [head, ...tail] =>
    switch (head) {
    | '"' => Some(tail |> parseString)
    /* | '{' => tail |> parseObject */
    | _ =>
      Js.log("Error parsing value!");
      None;
    }
  };

let execute = () => myString |> explode |> parseValue |> Js.log;
/* let parseMembers = json : members =>
   switch (json) {
   | [] =>
     Js.log("Empty?!");
     Pair(("error", String_("error")));
   | [head, ...tail] =>
     switch (head) {
     | '"' => {}
     | _ =>
       Js.log("Error parsing object!");
       Pair(("error", String_("error")));
     }
   }; */
/* let parseObject = json : object_ =>
   switch (json) {
   | [] =>
     Js.log("Empty?!");
     EmptyObject;
   | [head, ...tail] =>
     switch (head) {
     | '}' => EmptyObject
     | _ => parseMembers(tail)
   };



   myJson |> explode |> parseValue |> Js.log; */