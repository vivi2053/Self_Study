FROM node:14-alpine
RUN apk update
RUN apk add git
WORKDIR /
RUN git clone https://github.com/codecreator2053/Todo-React-App.git
WORKDIR /Todo-React-App/
RUN npm install 
CMD ["npm", "start"]