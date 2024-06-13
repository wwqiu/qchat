import qianfan

class Conversation:
    def __init__(self, model="ERNIE-Speed-8K"):
        self.chat_comp = qianfan.ChatCompletion()
        self.model = model
        self.messages = []

    def add_user_message(self, message):
        self.messages.append({
            "role": "user",
            "content": message
        })
    
    def add_assistant_message(self, message):
        self.messages.append({
            "role": "assistant",
            "content": message
        })

    def do(self):
        resp = self.chat_comp.do(model=self.model, messages=self.messages, stream=True)
        assistant_message = ""
        for r in resp:
            msg = r["body"]["result"]
            assistant_message += msg
            yield msg
        self.add_assistant_message(assistant_message)
        return None