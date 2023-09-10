import React, { Component } from "react";
import TodoForm from "./TodoForm";
import TodoItem from "./TodoItems";
import shortid from "shortid";

const minLeng = 4;
const maxLeng = 100;

export default class TodoList extends Component {
  state = {
    inputText: "",
    displayError: false,
    todolist: [{ id: "HLdsoudSDjshd", text: "do laundry", complete: true }],
    filter: "all",
    toggleAll: true,
  };
  handleChange = (event) => {
    this.setState({ inputText: event.target.value });
  };
  handleSubmit = (event) => {
    event.preventDefault();
    if (
      this.state.inputText.length < minLeng ||
      this.state.inputText.length > maxLeng
    ) {
      this.setState({ displayError: true });
    } else {
      this.setState({
        todolist: [
          {
            id: shortid.generate(),
            text: this.state.inputText,
            complete: false,
          },
          ...this.state.todolist,
        ],
        displayError: false,
        inputText: "",
        filter: "all",
      });
    }
  };

  handleChecked = (id) => {
    // const id = 'gdsagasdgasd'
    this.setState({
      todolist: this.state.todolist.map((todoitem) => {
        if (todoitem.id === id) {
          return { ...todoitem, complete: !todoitem.complete };
        } else {
          return todoitem;
        }
      }),
    });
  };

  handleDelete = (id) => {
    this.setState({
      todolist: this.state.todolist.filter((todo) => todo.id !== id),
    });
  };

  deleteFinished = () => {
    this.setState({
      todolist: this.state.todolist.filter((todo) => !todo.complete),
    });
  };

  render() {
    var completed = this.state.todolist.some((x) => x.complete);
    var item_candidates = {
      all: this.state.todolist,
      completed: this.state.todolist.filter((x) => x.complete),
      active: this.state.todolist.filter((x) => !x.complete),
    };
    return (
      <div>
        <TodoForm
          onSubmit={this.handleSubmit}
          onChange={this.handleChange}
          displayError={this.state.displayError}
          inputText={this.state.inputText}
          minLeng={minLeng}
          maxLeng={maxLeng}
        />

        <div>
          <div className="listItems">
            {item_candidates[this.state.filter].map((todo) => (
              <div key={todo.id}>
                <TodoItem
                  text={todo.text}
                  complete={todo.complete}
                  handleChecked={() => {
                    this.handleChecked(todo.id);
                  }}
                  handleDelete={() => {
                    this.handleDelete(todo.id);
                  }}
                />
              </div>
            ))}
          </div>
          <button
            style={{
              marginTop: "20px",
              display: completed ? "inline" : "none",
            }}
            onClick={this.deleteFinished}
          >
            Delete Finished
          </button>
        </div>
        <br />
        <div>
          todos left: {this.state.todolist.filter((x) => !x.complete).length}
        </div>
        <div>
          <button
            onClick={() => {
              this.setState({ filter: "all" });
            }}
          >
            all
          </button>
          <button
            onClick={() => {
              this.setState({ filter: "active" });
            }}
          >
            active
          </button>
          <button
            onClick={() => {
              this.setState({ filter: "completed" });
            }}
          >
            completed
          </button>
        </div>
        <div>
          <button
            onClick={() =>
              this.setState({
                toggleAll: !this.state.toggleAll,
                todolist: this.state.todolist.map((todo) => ({
                  ...todo,
                  complete: this.state.toggleAll,
                })),
              })
            }
          >
            check all items {`${this.state.toggleAll}`}
          </button>
        </div>
      </div>
    );
  }
}
