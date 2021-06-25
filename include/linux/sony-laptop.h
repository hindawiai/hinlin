<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SONYLAPTOP_H_
#घोषणा _SONYLAPTOP_H_

#समावेश <linux/types.h>

#अगर_घोषित __KERNEL__

/* used only क्रम communication between v4l and sony-laptop */

#घोषणा SONY_PIC_COMMAND_GETCAMERA		 1	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERA		 2
#घोषणा SONY_PIC_COMMAND_GETCAMERABRIGHTNESS	 3	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERABRIGHTNESS	 4
#घोषणा SONY_PIC_COMMAND_GETCAMERACONTRAST	 5	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERACONTRAST	 6
#घोषणा SONY_PIC_COMMAND_GETCAMERAHUE		 7	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERAHUE		 8
#घोषणा SONY_PIC_COMMAND_GETCAMERACOLOR		 9	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERACOLOR		10
#घोषणा SONY_PIC_COMMAND_GETCAMERASHARPNESS	11	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERASHARPNESS	12
#घोषणा SONY_PIC_COMMAND_GETCAMERAPICTURE	13	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERAPICTURE	14
#घोषणा SONY_PIC_COMMAND_GETCAMERAAGC		15	/* obsolete */
#घोषणा SONY_PIC_COMMAND_SETCAMERAAGC		16
#घोषणा SONY_PIC_COMMAND_GETCAMERAसूचीECTION	17	/* obsolete */
#घोषणा SONY_PIC_COMMAND_GETCAMERAROMVERSION	18	/* obsolete */
#घोषणा SONY_PIC_COMMAND_GETCAMERAREVISION	19	/* obsolete */

#अगर IS_ENABLED(CONFIG_SONY_LAPTOP)
पूर्णांक sony_pic_camera_command(पूर्णांक command, u8 value);
#अन्यथा
अटल अंतरभूत पूर्णांक sony_pic_camera_command(पूर्णांक command, u8 value) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __KERNEL__ */

#पूर्ण_अगर /* _SONYLAPTOP_H_ */
