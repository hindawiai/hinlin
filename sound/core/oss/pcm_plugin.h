<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __PCM_PLUGIN_H
#घोषणा __PCM_PLUGIN_H

/*
 *  Digital Audio (Plugin पूर्णांकerface) असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#अगर_घोषित CONFIG_SND_PCM_OSS_PLUGINS

#घोषणा snd_pcm_plug_stream(plug) ((plug)->stream)

क्रमागत snd_pcm_plugin_action अणु
	INIT = 0,
	PREPARE = 1,
पूर्ण;

काष्ठा snd_pcm_channel_area अणु
	व्योम *addr;			/* base address of channel samples */
	अचिन्हित पूर्णांक first;		/* offset to first sample in bits */
	अचिन्हित पूर्णांक step;		/* samples distance in bits */
पूर्ण;

काष्ठा snd_pcm_plugin_channel अणु
	व्योम *aptr;			/* poपूर्णांकer to the allocated area */
	काष्ठा snd_pcm_channel_area area;
	snd_pcm_uframes_t frames;	/* allocated frames */
	अचिन्हित पूर्णांक enabled:1;		/* channel need to be processed */
	अचिन्हित पूर्णांक wanted:1;		/* channel is wanted */
पूर्ण;

काष्ठा snd_pcm_plugin_क्रमmat अणु
	snd_pcm_क्रमmat_t क्रमmat;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक channels;
पूर्ण;

काष्ठा snd_pcm_plugin अणु
	स्थिर अक्षर *name;		/* plug-in name */
	पूर्णांक stream;
	काष्ठा snd_pcm_plugin_क्रमmat src_क्रमmat;	/* source क्रमmat */
	काष्ठा snd_pcm_plugin_क्रमmat dst_क्रमmat;	/* destination क्रमmat */
	पूर्णांक src_width;			/* sample width in bits */
	पूर्णांक dst_width;			/* sample width in bits */
	snd_pcm_access_t access;
	snd_pcm_sframes_t (*src_frames)(काष्ठा snd_pcm_plugin *plugin, snd_pcm_uframes_t dst_frames);
	snd_pcm_sframes_t (*dst_frames)(काष्ठा snd_pcm_plugin *plugin, snd_pcm_uframes_t src_frames);
	snd_pcm_sframes_t (*client_channels)(काष्ठा snd_pcm_plugin *plugin,
					     snd_pcm_uframes_t frames,
					     काष्ठा snd_pcm_plugin_channel **channels);
	snd_pcm_sframes_t (*transfer)(काष्ठा snd_pcm_plugin *plugin,
				      स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
				      काष्ठा snd_pcm_plugin_channel *dst_channels,
				      snd_pcm_uframes_t frames);
	पूर्णांक (*action)(काष्ठा snd_pcm_plugin *plugin,
		      क्रमागत snd_pcm_plugin_action action,
		      अचिन्हित दीर्घ data);
	काष्ठा snd_pcm_plugin *prev;
	काष्ठा snd_pcm_plugin *next;
	काष्ठा snd_pcm_substream *plug;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_pcm_plugin *plugin);
	अक्षर *buf;
	snd_pcm_uframes_t buf_frames;
	काष्ठा snd_pcm_plugin_channel *buf_channels;
	अक्षर extra_data[];
पूर्ण;

पूर्णांक snd_pcm_plugin_build(काष्ठा snd_pcm_substream *handle,
                         स्थिर अक्षर *name,
                         काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
                         काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
                         माप_प्रकार extra,
                         काष्ठा snd_pcm_plugin **ret);
पूर्णांक snd_pcm_plugin_मुक्त(काष्ठा snd_pcm_plugin *plugin);
पूर्णांक snd_pcm_plugin_clear(काष्ठा snd_pcm_plugin **first);
पूर्णांक snd_pcm_plug_alloc(काष्ठा snd_pcm_substream *plug, snd_pcm_uframes_t frames);
snd_pcm_sframes_t snd_pcm_plug_client_size(काष्ठा snd_pcm_substream *handle, snd_pcm_uframes_t drv_size);
snd_pcm_sframes_t snd_pcm_plug_slave_size(काष्ठा snd_pcm_substream *handle, snd_pcm_uframes_t clt_size);

#घोषणा FULL ROUTE_PLUGIN_RESOLUTION
#घोषणा HALF ROUTE_PLUGIN_RESOLUTION / 2

पूर्णांक snd_pcm_plugin_build_io(काष्ठा snd_pcm_substream *handle,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_pcm_plugin **r_plugin);
पूर्णांक snd_pcm_plugin_build_linear(काष्ठा snd_pcm_substream *handle,
				काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
				काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
				काष्ठा snd_pcm_plugin **r_plugin);
पूर्णांक snd_pcm_plugin_build_mulaw(काष्ठा snd_pcm_substream *handle,
			       काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			       काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			       काष्ठा snd_pcm_plugin **r_plugin);
पूर्णांक snd_pcm_plugin_build_rate(काष्ठा snd_pcm_substream *handle,
			      काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			      काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			      काष्ठा snd_pcm_plugin **r_plugin);
पूर्णांक snd_pcm_plugin_build_route(काष्ठा snd_pcm_substream *handle,
			       काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			       काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
		               काष्ठा snd_pcm_plugin **r_plugin);
पूर्णांक snd_pcm_plugin_build_copy(काष्ठा snd_pcm_substream *handle,
			      काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			      काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			      काष्ठा snd_pcm_plugin **r_plugin);

पूर्णांक snd_pcm_plug_क्रमmat_plugins(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_params *slave_params);

snd_pcm_क्रमmat_t snd_pcm_plug_slave_क्रमmat(snd_pcm_क्रमmat_t क्रमmat,
					   स्थिर काष्ठा snd_mask *क्रमmat_mask);

पूर्णांक snd_pcm_plugin_append(काष्ठा snd_pcm_plugin *plugin);

snd_pcm_sframes_t snd_pcm_plug_ग_लिखो_transfer(काष्ठा snd_pcm_substream *handle,
					      काष्ठा snd_pcm_plugin_channel *src_channels,
					      snd_pcm_uframes_t size);
snd_pcm_sframes_t snd_pcm_plug_पढ़ो_transfer(काष्ठा snd_pcm_substream *handle,
					     काष्ठा snd_pcm_plugin_channel *dst_channels_final,
					     snd_pcm_uframes_t size);

snd_pcm_sframes_t snd_pcm_plug_client_channels_buf(काष्ठा snd_pcm_substream *handle,
						   अक्षर *buf, snd_pcm_uframes_t count,
						   काष्ठा snd_pcm_plugin_channel **channels);

snd_pcm_sframes_t snd_pcm_plugin_client_channels(काष्ठा snd_pcm_plugin *plugin,
						 snd_pcm_uframes_t frames,
						 काष्ठा snd_pcm_plugin_channel **channels);

पूर्णांक snd_pcm_area_silence(स्थिर काष्ठा snd_pcm_channel_area *dst_channel,
			 माप_प्रकार dst_offset,
			 माप_प्रकार samples, snd_pcm_क्रमmat_t क्रमmat);
पूर्णांक snd_pcm_area_copy(स्थिर काष्ठा snd_pcm_channel_area *src_channel,
		      माप_प्रकार src_offset,
		      स्थिर काष्ठा snd_pcm_channel_area *dst_channel,
		      माप_प्रकार dst_offset,
		      माप_प्रकार samples, snd_pcm_क्रमmat_t क्रमmat);

व्योम *snd_pcm_plug_buf_alloc(काष्ठा snd_pcm_substream *plug, snd_pcm_uframes_t size);
व्योम snd_pcm_plug_buf_unlock(काष्ठा snd_pcm_substream *plug, व्योम *ptr);
snd_pcm_sframes_t snd_pcm_oss_ग_लिखो3(काष्ठा snd_pcm_substream *substream,
				     स्थिर अक्षर *ptr, snd_pcm_uframes_t size,
				     पूर्णांक in_kernel);
snd_pcm_sframes_t snd_pcm_oss_पढ़ो3(काष्ठा snd_pcm_substream *substream,
				    अक्षर *ptr, snd_pcm_uframes_t size, पूर्णांक in_kernel);
snd_pcm_sframes_t snd_pcm_oss_ग_लिखोv3(काष्ठा snd_pcm_substream *substream,
				      व्योम **bufs, snd_pcm_uframes_t frames);
snd_pcm_sframes_t snd_pcm_oss_पढ़ोv3(काष्ठा snd_pcm_substream *substream,
				     व्योम **bufs, snd_pcm_uframes_t frames);

#अन्यथा

अटल अंतरभूत snd_pcm_sframes_t snd_pcm_plug_client_size(काष्ठा snd_pcm_substream *handle, snd_pcm_uframes_t drv_size) अणु वापस drv_size; पूर्ण
अटल अंतरभूत snd_pcm_sframes_t snd_pcm_plug_slave_size(काष्ठा snd_pcm_substream *handle, snd_pcm_uframes_t clt_size) अणु वापस clt_size; पूर्ण
अटल अंतरभूत पूर्णांक snd_pcm_plug_slave_क्रमmat(पूर्णांक क्रमmat, स्थिर काष्ठा snd_mask *क्रमmat_mask) अणु वापस क्रमmat; पूर्ण

#पूर्ण_अगर

#अगर_घोषित PLUGIN_DEBUG
#घोषणा pdम_लिखो(fmt, args...) prपूर्णांकk(KERN_DEBUG "plugin: " fmt, ##args)
#अन्यथा
#घोषणा pdम_लिखो(fmt, args...)
#पूर्ण_अगर

#पूर्ण_अगर				/* __PCM_PLUGIN_H */
