<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_MATROXFB_H__
#घोषणा __LINUX_MATROXFB_H__

#समावेश <यंत्र/ioctl.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/fb.h>

काष्ठा matroxioc_output_mode अणु
	__u32	output;		/* which output */
#घोषणा MATROXFB_OUTPUT_PRIMARY		0x0000
#घोषणा MATROXFB_OUTPUT_SECONDARY	0x0001
#घोषणा MATROXFB_OUTPUT_DFP		0x0002
	__u32	mode;		/* which mode */
#घोषणा MATROXFB_OUTPUT_MODE_PAL	0x0001
#घोषणा MATROXFB_OUTPUT_MODE_NTSC	0x0002
#घोषणा MATROXFB_OUTPUT_MODE_MONITOR	0x0080
पूर्ण;
#घोषणा MATROXFB_SET_OUTPUT_MODE	_IOW('n',0xFA,माप_प्रकार)
#घोषणा MATROXFB_GET_OUTPUT_MODE	_IOWR('n',0xFA,माप_प्रकार)

/* bitfield */
#घोषणा MATROXFB_OUTPUT_CONN_PRIMARY	(1 << MATROXFB_OUTPUT_PRIMARY)
#घोषणा MATROXFB_OUTPUT_CONN_SECONDARY	(1 << MATROXFB_OUTPUT_SECONDARY)
#घोषणा MATROXFB_OUTPUT_CONN_DFP	(1 << MATROXFB_OUTPUT_DFP)
/* connect these outमाला_दो to this framebuffer */
#घोषणा MATROXFB_SET_OUTPUT_CONNECTION	_IOW('n',0xF8,माप_प्रकार)
/* which outमाला_दो are connected to this framebuffer */
#घोषणा MATROXFB_GET_OUTPUT_CONNECTION	_IOR('n',0xF8,माप_प्रकार)
/* which outमाला_दो are available क्रम this framebuffer */
#घोषणा MATROXFB_GET_AVAILABLE_OUTPUTS	_IOR('n',0xF9,माप_प्रकार)
/* which outमाला_दो exist on this framebuffer */
#घोषणा MATROXFB_GET_ALL_OUTPUTS	_IOR('n',0xFB,माप_प्रकार)

क्रमागत matroxfb_ctrl_id अणु
  MATROXFB_CID_TESTOUT	 = V4L2_CID_PRIVATE_BASE,
  MATROXFB_CID_DEFLICKER,
  MATROXFB_CID_LAST
पूर्ण;

#पूर्ण_अगर

