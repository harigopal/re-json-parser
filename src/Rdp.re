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

let myJson = "{\"hello\":\"world\"}";

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

let extractString = json => {
  let rec aux = (sublist, json) =>
    switch (json) {
    | [] =>
      Js.log("Couldn't find close double-quote for string!");
      ([], []);
    | [h, ...t] => h == '"' ? (sublist, t) : aux([h, ...sublist], t)
    };
  let (s, remainder) = aux([], json);
  /* Reverse the string to make it look right. */
  (s |> List.rev |> implode, remainder);
};

let parseString = json => {
  let (s, remainder) = extractString(json);
  (String_(s), remainder);
};

let rec parseMembers = json =>
  switch (json) {
  | [] =>
    Js.log("Empty Member?!");
    (Pair(("error", String_("error"))), []);
  | [head, ..._tail] =>
    switch (head) {
    | '"' =>
      let (pair, remainder) = parsePair(json);
      switch (remainder) {
      | [] =>
        Js.log("Pair's remainder is empty!");
        (Pair(pair), []);
      | [head, ...tail] =>
        switch (head) {
        | '}' => (Pair(pair), tail)
        | ',' =>
          let (members, remainder) = parseMembers(tail);
          (PairAndMembers(pair, members), remainder);
        | _ =>
          Js.log("Pair is not followed by closing bracket or comma!");
          (Pair(pair), []);
        }
      };
    | _ =>
      Js.log("Member doesn't begin with \" character!");
      (Pair(("error", String_("error"))), []);
    }
  }
and parsePair = json =>
  switch (json) {
  | [] =>
    Js.log("Empty Pair?!");
    (("error", String_("error")), []);
  | [head, ...tail] =>
    switch (head) {
    | '"' =>
      let (key, remainder) = tail |> extractString;
      let (value, rest) =
        switch (remainder) {
        | [] =>
          Js.log("Remainder after key for Pair is empty!");
          (String_("error"), []);
        | [head, ...tail] =>
          switch (head) {
          | ':' => parseValue(tail)
          | _ =>
            Js.log("Value separator for Pair is missing!");
            (String_("error"), []);
          }
        };
      ((key, value), rest);
    | _ =>
      Js.log("Pair does not start with a double-quote!");
      (("error", String_("error")), []);
    }
  }
and parseValue = json =>
  switch (json) {
  | [] => (String_("Empty!"), [])
  | [head, ...tail] =>
    switch (head) {
    | '"' => tail |> parseString
    | '{' => tail |> parseObject
    | c =>
      Js.log(
        "Invalid beginning character '" ++ String.make(1, c) ++ "' for value!",
      );
      (String_("Error!"), []);
    }
  }
and parseObject = json =>
  switch (json) {
  | [] =>
    Js.log("Empty Object?!");
    (Object_(EmptyObject), []);
  | [head, ..._tail] =>
    switch (head) {
    | '}' => (Object_(EmptyObject), [])
    | _ =>
      let (members, remainder) = parseMembers(json);
      (Object_(ObjectWithMembers(members)), remainder);
    }
  };

let execute = () => {
  let v = myJson |> explode |> parseValue;
  v |> Js.log;
};