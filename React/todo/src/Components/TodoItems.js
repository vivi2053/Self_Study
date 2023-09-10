import React from 'react';
import './TodoItems.css';
import logo from './../logo.svg'

export default class TodoItem extends React.Component{
    render(){
        return(
            <div className="singleItem">
                    <input className="checkBox" checked={this.props.complete} onChange={this.props.handleChecked} type="checkbox"/>
                    <label className="itemLabel">{this.props.text}</label>
                    <button className="deleteButton" onClick={this.props.handleDelete}><img src={logo} height='20px' width='20px' alt='del_logo'/></button>
            </div>
        );
    }
}