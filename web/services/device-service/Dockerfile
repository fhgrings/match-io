FROM python:3.7

COPY . /app

WORKDIR /app

RUN pip install -r requirements.txt

RUN pip install gunicorn

EXPOSE 7080

CMD ["gunicorn","--bind", "0.0.0.0:7080", "src.app:create_app()"]