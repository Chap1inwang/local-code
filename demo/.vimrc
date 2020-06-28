"**************************************************************************************
"vundle配置
"**************************************************************************************
"
"
set nocompatible              
filetype off                  

set rtp+=~/.vim/bundle/Vundle
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'jiangmiao/auto-pairs'
Plugin 'dense-analysis/ale'
Plugin 'octol/vim-cpp-enhanced-highlight'
"Plugin 'Valloric/YouCompleteMe'
Plugin 'Sirver/ultisnips'
Plugin 'SuperTab'
Bundle "nine2/vim-indent-guides"
Plugin 'Shougo/deoplete-clangx'

call vundle#end()           


if has('nvim')
  Plugin 'Shougo/deoplete.nvim', { 'do': ':UpdateRemotePlugins' }
else
  Plugin 'Shougo/deoplete.nvim'
  Plugin 'roxma/nvim-yarp'
  Plugin 'roxma/vim-hug-neovim-rpc'
endif
let g:deoplete#enable_at_startup = 1


filetype plugin indent on  
"
" 常用的命令
" :PluginList       - 列出所有已配置的插件
" :PluginInstall     - 安装插件,追加 `!` 用以更新或使用 :PluginUpdate
" :PluginSearch foo - 搜索 foo ; 追加 `!` 清除本地缓存
" :PluginClean      - 清除未使用插件,需要确认; 追加 `!` 自动批准移除未使用插件
" ****************************************************************************************
"vim常规设置
"*****************************************************************************************
"
"
set mouse=a                      "支持鼠标定位
set enc=utf-8                    "设置编码格式
set nu                           "左侧行号
set tabstop=4                    "tab 长度设置为 4
set nobackup                     "覆盖文件时不备份
set cursorline                   "突出显示当前行
set ruler                        "在右下角显示光标位置的状态行
set autoindent                   " 继承前一行的缩进方式
set nocompatible                 "关闭vi兼容  
set history=500                  "历史命令  
syntax on                        "语法高亮  
set smartindent                  "智能缩进  
set showmatch                    "括号匹配  
set incsearch                    "设置快速搜索  
set foldenable                   "开启代码折叠  
filetype plugin on               "文件关联
filetype indent on               "根据文件类型缩进
set ic                           "忽略大小写
set showmatch                    "显示匹配的括号
set tabstop=4			 "设置所有的Tab和缩进为4个空格
set noswapfile			 "没有备份
set cindent 			 "c/c++自动缩进"
set smartindent
set autoindent			 "参考上一行的缩进方式进行自动缩进"
filetype indent on		 "根据文件类型进行缩进"
set softtabstop=4 		 "4 character as a tab"
set shiftwidth=4
set smarttab 
set pyxversion=3

"let g:SuperTabRetainCompletionType=2  "supertab配置
let g:SuperTabDefaultCompletionType="context" "按tab循环选择

"*************************************************buffer配置***********************************************
let g:miniBufExplMapCTabSwitchBufs = 1
let g:miniBufExplMapWindowNavVim = 1 
let g:miniBufExplMapWindowNavArrows = 1 
let g:miniBufExplModSelTarget = 1
let g:miniBufExplMoreThanOne=0

"***********************************************************************************************************
"***************************************************************************************************
"************************************************************************************************************ 

 

