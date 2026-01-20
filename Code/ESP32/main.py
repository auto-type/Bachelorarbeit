from fastapi import FastAPI

app = FastAPI()

touches = []

@app.get("/")
def read_root():
    return {"message": "Hello World"}

@app.get("/touch/input/pw={pw}&wert={touch}")
def read_touch(pw: str, touch: int):
    if(touch == 1): touches.append(touch)
    return {"message" : "Received information from Station with password: " + pw,
            "touch" : touch,
            "touches since start" : len(touches)}
