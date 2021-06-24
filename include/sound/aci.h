<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ACI_H_
#घोषणा _ACI_H_

#घोषणा ACI_REG_COMMAND		0	/* ग_लिखो रेजिस्टर offset */
#घोषणा ACI_REG_STATUS		1	/* पढ़ो रेजिस्टर offset */
#घोषणा ACI_REG_BUSY		2	/* busy रेजिस्टर offset */
#घोषणा ACI_REG_RDS		2	/* PCM20: RDS रेजिस्टर offset */
#घोषणा ACI_MINTIME		500	/* ACI समय out limit */

#घोषणा ACI_SET_MUTE		0x0d
#घोषणा ACI_SET_POWERAMP	0x0f
#घोषणा ACI_SET_TUNERMUTE	0xa3
#घोषणा ACI_SET_TUNERMONO	0xa4
#घोषणा ACI_SET_IDE		0xd0
#घोषणा ACI_SET_WSS		0xd1
#घोषणा ACI_SET_SOLOMODE	0xd2
#घोषणा ACI_SET_PREAMP		0x03
#घोषणा ACI_GET_PREAMP		0x21
#घोषणा ACI_WRITE_TUNE		0xa7
#घोषणा ACI_READ_TUNERSTEREO	0xa8
#घोषणा ACI_READ_TUNERSTATION	0xa9
#घोषणा ACI_READ_VERSION	0xf1
#घोषणा ACI_READ_IDCODE		0xf2
#घोषणा ACI_INIT		0xff
#घोषणा ACI_STATUS		0xf0
#घोषणा ACI_S_GENERAL		0x00
#घोषणा ACI_ERROR_OP		0xdf

/* ACI Mixer */

/* These are the values क्रम the right channel GET रेजिस्टरs.
   Add an offset of 0x01 क्रम the left channel रेजिस्टर.
   (left=right+0x01) */

#घोषणा ACI_GET_MASTER		0x03
#घोषणा ACI_GET_MIC		0x05
#घोषणा ACI_GET_LINE		0x07
#घोषणा ACI_GET_CD		0x09
#घोषणा ACI_GET_SYNTH		0x0b
#घोषणा ACI_GET_PCM		0x0d
#घोषणा ACI_GET_LINE1		0x10	/* Radio on PCM20 */
#घोषणा ACI_GET_LINE2		0x12

#घोषणा ACI_GET_EQ1		0x22	/* from Bass ... */
#घोषणा ACI_GET_EQ2		0x24
#घोषणा ACI_GET_EQ3		0x26
#घोषणा ACI_GET_EQ4		0x28
#घोषणा ACI_GET_EQ5		0x2a
#घोषणा ACI_GET_EQ6		0x2c
#घोषणा ACI_GET_EQ7		0x2e	/* ... to Treble */

/* And these are the values क्रम the right channel SET रेजिस्टरs.
   For left channel access you have to add an offset of 0x08.
   MASTER is an exception, which needs an offset of 0x01 */

#घोषणा ACI_SET_MASTER		0x00
#घोषणा ACI_SET_MIC		0x30
#घोषणा ACI_SET_LINE		0x31
#घोषणा ACI_SET_CD		0x34
#घोषणा ACI_SET_SYNTH		0x33
#घोषणा ACI_SET_PCM		0x32
#घोषणा ACI_SET_LINE1		0x35	/* Radio on PCM20 */
#घोषणा ACI_SET_LINE2		0x36

#घोषणा ACI_SET_EQ1		0x40	/* from Bass ... */
#घोषणा ACI_SET_EQ2		0x41
#घोषणा ACI_SET_EQ3		0x42
#घोषणा ACI_SET_EQ4		0x43
#घोषणा ACI_SET_EQ5		0x44
#घोषणा ACI_SET_EQ6		0x45
#घोषणा ACI_SET_EQ7		0x46	/* ... to Treble */

काष्ठा snd_miro_aci अणु
	अचिन्हित दीर्घ aci_port;
	पूर्णांक aci_venकरोr;
	पूर्णांक aci_product;
	पूर्णांक aci_version;
	पूर्णांक aci_amp;
	पूर्णांक aci_preamp;
	पूर्णांक aci_solomode;

	काष्ठा mutex aci_mutex;
पूर्ण;

पूर्णांक snd_aci_cmd(काष्ठा snd_miro_aci *aci, पूर्णांक ग_लिखो1, पूर्णांक ग_लिखो2, पूर्णांक ग_लिखो3);

काष्ठा snd_miro_aci *snd_aci_get_aci(व्योम);

#पूर्ण_अगर  /* _ACI_H_ */

