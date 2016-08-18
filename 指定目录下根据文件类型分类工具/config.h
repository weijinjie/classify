#ifndef _WJJ_CONFIG_HEAD
#define _WJJ_CONFIG_HEAD


/**
  * 支持搜索的文件类型*/
static char* searchFileType[] = {
	".h",
	".c",
	".cpp",
	".java",
	".php",
	".pdf",
	".doc",
	".md",
	".txt",
	".mp4",
	".avi",
	".wmv",
	".rmvb",
	".jpg",
	".gif",
	".png",
	".bmp",
	".mp3",
	".wav",
	".dll",
	".lib",
	".html",
	".xml",
	".js",
	".ppt",
	".xlsx"
};

/**
  * 支持搜索文件类型的个数*/
static int sFTCount = sizeof(searchFileType) / sizeof(char*);



#endif

