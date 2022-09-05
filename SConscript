# RT-Thread building script for bridge

from building import *

cwd      = GetCurrentDir()
src      = Glob('src/*.c')
src     += Glob('adapter/*.c')

CPPPATH  = [cwd + '/inc']

group = DefineGroup('agile_upgrade', src, depend = ['PKG_USING_AGILE_UPGRADE'], CPPPATH = CPPPATH)

Return('group')
