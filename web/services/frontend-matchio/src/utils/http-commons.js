import axios from 'axios';

export const HTTP = axios.create({
  baseURL: `http://172.17.0.1:7080`,
  headers: {
    Authorization: 'Bearer {token}'
  }
})