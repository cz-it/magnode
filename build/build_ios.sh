#!/usr/bin/env sh
echo "Building iOS ..."
source ./utils/shutil.sh
source ./utils/helper.sh
CWD=`pwd`
parse_args $@
debug_flag=$?

ios_sdk=`xcodebuild -showsdks 2>/dev/null | grep "sdk iphoneos" | awk '{print $4}'`

cd $CWD
ver=1.0.1

function copy2dist_release()
{
	echo "Copy to distribution direcoty..."
	cd $CWD
}

function copy2dist_debug()
{
	echo "Copy to distribution direcoty..."
	cd $CWD
}

function build_xcode_release()
{
	#	runcmd xcodebuild   -configuration Release -sdk ${ios_sdk} -destination 'platform=iOS,arch=\"arm64 armv7 armv7s\"'
	runcmd xcodebuild   -configuration Release -sdk ${ios_sdk} -destination 'platform=iOS'
}

function build_xcode_debug()
{
	runcmd xcodebuild   -configuration Debug  -sdk ${ios_sdk} -destination 'platform=iOS'
}

function clean_xcode()
{
	runcmd xcodebuild  clean   -configuration Debug   -sdk ${ios_sdk} -destination 'platform=iOS'
	runcmd xcodebuild  clean   -configuration Release -sdk ${ios_sdk} -destination 'platform=iOS'
}


function build_projs_debug()
{
	cd $CWD && cd ./iOS/magnode/ && build_xcode_debug
	cd $CWD
}

function build_projs_release()
{
	cd $CWD
	cd $CWD && cd ./iOS/magnode/ && build_xcode_release
	cd $CWD
}

function clean_projs()
{
	cd $CWD
	cd $CWD && cd ./iOS/magnode/ && clean_xcode && rm -rf build
	cd $CWD

}

cd $CWD
cd ./iOS/TVE/
if [ $debug_flag == $RELEASE ]; then
    echo "Build Release Library ..."
	build_projs_release
	copy2dist_release
    succ_exit
elif [ $debug_flag == $DEBUG ]; then
    echo "Build Debug Library ..."
	build_projs_debug
	copy2dist_debug
    succ_exit
elif [ $debug_flag == $CLEAN ]; then
    echo "Clean Project ..."
	clean_projs
    cancel_exit
else 
    fail_exit
fi

