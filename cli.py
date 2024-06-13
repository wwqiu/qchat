
import os
from qchat.conversation import Conversation
conv = Conversation(model="ERNIE-Speed-8K")

from rich.console import Console
from rich.markdown import Markdown
from rich.live import Live
from rich.panel import Panel

class MarkdownRenderer:
    def __init__(self):
        self.msg = ""
        self.live = Live()

    def print(self, msg:str):
        self.msg += msg
        md = Markdown(self.msg)
        console = Console()
    
    def start_live(self, header:str="QChat: "):
        self.msg = ""
        self.live.start()

    def stop_live(self):
        self.live.stop()

    def print_stream(self, msg:str):
        for c in msg:
            self.msg += c
            md = Markdown(self.msg)
            self.live.update(Panel(md, title="QChat", title_align="left", padding=1), refresh=True)
            os.system("sleep 0.03")
        
while True:
    console = Console()
    user_input = console.input(("You: "))
    console.print()
    conv.add_user_message(user_input)
    renderer = MarkdownRenderer()
    renderer.start_live()
    for msg in conv.do():
        if msg is not None:
            renderer.print_stream(msg)
    renderer.stop_live()
    console.print()