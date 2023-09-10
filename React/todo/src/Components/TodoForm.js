import React from 'react';
import './TodoForm.css'



export default class TodoForm extends React.Component{

    render() {
        return (
            <div>
                <form onSubmit={this.props.onSubmit}>
                <input className='todoInput' 
                value={this.props.inputText} 
                placeholder='write your todo' 
                onChange={this.props.onChange}/>
                <label className="errorLabel" style={{display: this.props.displayError?'block':'none'}}>
                    todo items should be {this.props.minLeng} to {this.props.maxLeng} characters long
                    </label>
                <br />
                <button className="submitButton"  type='submit'>Add Todo</button>
                </form>
            </div>
        );
    }
}