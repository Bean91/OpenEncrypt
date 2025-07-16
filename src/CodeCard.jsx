import React, {useState} from "react";


function CodeCard(props) {
    const [key, setKey] = useState("");
    const [msg, setMsg] = useState("");

    function changeKey(e) {
        setKey(e.target.value);
    }

    function changeMsg(e) {
        setMsg(e.target.value);
    }

    return (
        <div>
            <h1>{props.name}</h1>
            <div></div>
        </div>
    );
}