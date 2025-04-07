// AdapterPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

// 菜鸟教程
namespace LH1 {
// 媒体播放器
class MediaPlayer {
public:
	virtual void Play(std::string strAudioType, std::string strFileName) = 0;
};
// 高级媒体播放器
class AdvancedMediaPlayer {
public:
	virtual void PlayVlc(std::string strFileName) = 0;
	virtual void PlayMP4(std::string strFileName) = 0;
};

class VlcPlayer : public AdvancedMediaPlayer {
public:
	virtual void PlayVlc(std::string strFileName) override {
		std::cout << "Playing vlc file. Name: " << strFileName << "\n";
	}
	virtual void PlayMP4(std::string strFileName) override {
		// 什么也不做
	}

};

class Mp4Player : public AdvancedMediaPlayer {
public:
	virtual void PlayVlc(std::string strFileName) override {
		// 什么也不做
	}
	virtual void PlayMP4(std::string strFileName) override {
		std::cout << "Playing MP4 file. Name: " << strFileName << "\n";
	}
};



class MediaAdapter : MediaPlayer {
public:
	MediaAdapter(std::string audioType) {
		if (audioType.compare("vlc") == 0) {
			m_musicPlayer = new VlcPlayer();
		}
		else if (audioType.compare("mp4") == 0) {
			m_musicPlayer = new Mp4Player();
		}
	}
	virtual void Play(std::string strAudioType, std::string strFileName) override {
		if (strAudioType.compare("vlc") == 0) {
			m_musicPlayer->PlayVlc(strFileName);
		}
		else if (strAudioType.compare("mp4") == 0) {
			m_musicPlayer->PlayMP4(strFileName);
		}
	}
private:
	AdvancedMediaPlayer* m_musicPlayer;
};

class AudioPlayer : MediaPlayer {
public:
	//AudioPlayer(std::string audioType) {

	//}
 	virtual void Play(std::string strAudioType, std::string strFileName) override {
		//播放 mp3 音乐文件的内置支持
		if (strAudioType.compare("mp3") == 0) {
			std::cout << "Playing mp3 file. Name: " << strFileName << "\n";
		}
		//mediaAdapter 提供了播放其他文件格式的支持
		else if (strAudioType.compare("vlc") == 0 || strAudioType.compare("mp4") == 0) {
			m_mediaAdapter = new MediaAdapter(strAudioType);
			m_mediaAdapter->Play(strAudioType, strFileName);
		}
		else {
			std::cout << "Invalid media. " << strAudioType + " format not supported" << "\n";
		}
	}
	MediaAdapter* m_mediaAdapter;
};

void AdapterPatternDemo() {
	AudioPlayer* audioPlayer = new AudioPlayer();

	audioPlayer->Play("mp3", "beyond the horizon.mp3");
	audioPlayer->Play("mp4", "alone.mp4");
	audioPlayer->Play("vlc", "far far away.vlc");
	audioPlayer->Play("avi", "mind me.avi");
}

}

int main()
{
	LH1::AdapterPatternDemo();
    std::cout << "Hello World!\n";
}

