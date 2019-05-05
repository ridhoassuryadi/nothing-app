
[@bs.config {jsx: 3}]
open BsReactNative;

module Nothing = {

type colorType = 
  | Dark 
  | Light ;

type action =
  | ChangeTheme(colorType)

type state = colorType;

module Styles = {
  open Style;
  let createContainerStyle = (type_) => {
    let base =         style([
          flex(1.),
          justifyContent(Center),
          alignItems(Center),
        ]);

    let styleBasedOnType = 
      switch(type_){
        | Dark => style([backgroundColor(Constants.Color.black -> String)])
        | Light => style([backgroundColor(Constants.Color.white -> String)])
      }

    flatten([|base, styleBasedOnType|])
  }

  let createTextStyle = (type_) => {
    let base =         style([
          fontSize(Float(12.)),
          textAlign(Center),
          margin(Pt(10.)),
        ])

    let styleBasedOnType = 
      switch(type_){
        | Dark => style([color(Constants.Color.darkGrey -> String)])
        | Light => style([color(Constants.Color.grey -> String)])
      }
    
    flatten([|base, styleBasedOnType|])
  }
}

let dataType: array(colorType) = [|Light, Dark|];
  
[@react.component]
let make = (_children) => {
  let (state, dispatch) = React.useReducer(
    (_, action) =>
      switch (action) {
      | ChangeTheme(themeType)  => themeType
      },
    Light
  );

  React.useEffect(() => {
    let numRandom = Js.Math.floor(Js.Math.random() *. 2.)
    dispatch(ChangeTheme(dataType[numRandom]))
    None;
  });

  <View
    style=Styles.createContainerStyle(state)>
    <Text style=Styles.createTextStyle(state)>
      "Nothing"->ReasonReact.string
    </Text>
  </View>
};
}


let app = Nothing.make
