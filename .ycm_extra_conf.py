# -*- coding: utf-8 -*-

import os

flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-xc',
    '-std=c11',
]

def FlagsForFile(filename, **kwds):
    return {
        'flags' : flags,
        'include_paths_relative_to_dir' :
            os.path.dirname(os.path.abspath(__file__))
    }
