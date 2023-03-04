import ctypes as c
from WinJobsterLoader import WinJobsterLoader

class Process:
    _library = WinJobsterLoader().load()

    def __init__(self, cmdline: str, working_directory: str | None = None):
        self._handle = c.c_void_p(None)
        self._library.StartProcess(
            cmdline,
            working_directory,
            c.byref(self._handle))

    def is_alive(self) -> bool:
        return self._library.IsAlive(self._handle)

    def kill(self):
        self._library.Kill(self._handle)

    def __del__(self):
        if self._handle is not None:
            self._library.Cleanup(self._handle)
            self._handle = None
