<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AV7110_AV_H_
#घोषणा _AV7110_AV_H_

काष्ठा av7110;

बाह्य पूर्णांक av7110_set_vidmode(काष्ठा av7110 *av7110,
			      क्रमागत av7110_video_mode mode);

बाह्य पूर्णांक av7110_record_cb(काष्ठा dvb_filter_pes2ts *p2t, u8 *buf, माप_प्रकार len);
बाह्य पूर्णांक av7110_pes_play(व्योम *dest, काष्ठा dvb_ringbuffer *buf, पूर्णांक dlen);
बाह्य पूर्णांक av7110_ग_लिखो_to_decoder(काष्ठा dvb_demux_feed *feed, स्थिर u8 *buf, माप_प्रकार len);

बाह्य पूर्णांक av7110_set_volume(काष्ठा av7110 *av7110, अचिन्हित पूर्णांक volleft,
			     अचिन्हित पूर्णांक volright);
बाह्य पूर्णांक av7110_av_stop(काष्ठा av7110 *av7110, पूर्णांक av);
बाह्य पूर्णांक av7110_av_start_record(काष्ठा av7110 *av7110, पूर्णांक av,
			  काष्ठा dvb_demux_feed *dvbdmxfeed);
बाह्य पूर्णांक av7110_av_start_play(काष्ठा av7110 *av7110, पूर्णांक av);

बाह्य व्योम dvb_video_add_event(काष्ठा av7110 *av7110, काष्ठा video_event *event);

बाह्य व्योम av7110_p2t_init(काष्ठा av7110_p2t *p, काष्ठा dvb_demux_feed *feed);
बाह्य व्योम av7110_p2t_ग_लिखो(u8 स्थिर *buf, दीर्घ पूर्णांक length, u16 pid, काष्ठा av7110_p2t *p);

बाह्य पूर्णांक av7110_av_रेजिस्टर(काष्ठा av7110 *av7110);
बाह्य व्योम av7110_av_unरेजिस्टर(काष्ठा av7110 *av7110);
बाह्य पूर्णांक av7110_av_init(काष्ठा av7110 *av7110);
बाह्य व्योम av7110_av_निकास(काष्ठा av7110 *av7110);


#पूर्ण_अगर /* _AV7110_AV_H_ */
