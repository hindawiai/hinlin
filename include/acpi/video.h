<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ACPI_VIDEO_H
#घोषणा __ACPI_VIDEO_H

#समावेश <linux/त्रुटिसं.स> /* क्रम ENODEV */
#समावेश <linux/types.h> /* क्रम bool */

काष्ठा acpi_video_brightness_flags अणु
	u8 _BCL_no_ac_battery_levels:1;	/* no AC/Battery levels in _BCL */
	u8 _BCL_reversed:1;		/* _BCL package is in a reversed order */
	u8 _BQC_use_index:1;		/* _BQC वापसs an index value */
पूर्ण;

काष्ठा acpi_video_device_brightness अणु
	पूर्णांक curr;
	पूर्णांक count;
	पूर्णांक *levels;
	काष्ठा acpi_video_brightness_flags flags;
पूर्ण;

काष्ठा acpi_device;

#घोषणा ACPI_VIDEO_CLASS	"video"

#घोषणा ACPI_VIDEO_DISPLAY_CRT  1
#घोषणा ACPI_VIDEO_DISPLAY_TV   2
#घोषणा ACPI_VIDEO_DISPLAY_DVI  3
#घोषणा ACPI_VIDEO_DISPLAY_LCD  4

#घोषणा ACPI_VIDEO_DISPLAY_LEGACY_MONITOR 0x0100
#घोषणा ACPI_VIDEO_DISPLAY_LEGACY_PANEL   0x0110
#घोषणा ACPI_VIDEO_DISPLAY_LEGACY_TV      0x0200

#घोषणा ACPI_VIDEO_NOTIFY_SWITCH		0x80
#घोषणा ACPI_VIDEO_NOTIFY_PROBE			0x81
#घोषणा ACPI_VIDEO_NOTIFY_CYCLE			0x82
#घोषणा ACPI_VIDEO_NOTIFY_NEXT_OUTPUT		0x83
#घोषणा ACPI_VIDEO_NOTIFY_PREV_OUTPUT		0x84
#घोषणा ACPI_VIDEO_NOTIFY_CYCLE_BRIGHTNESS	0x85
#घोषणा ACPI_VIDEO_NOTIFY_INC_BRIGHTNESS	0x86
#घोषणा ACPI_VIDEO_NOTIFY_DEC_BRIGHTNESS	0x87
#घोषणा ACPI_VIDEO_NOTIFY_ZERO_BRIGHTNESS	0x88
#घोषणा ACPI_VIDEO_NOTIFY_DISPLAY_OFF		0x89

क्रमागत acpi_backlight_type अणु
	acpi_backlight_undef = -1,
	acpi_backlight_none = 0,
	acpi_backlight_video,
	acpi_backlight_venकरोr,
	acpi_backlight_native,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ACPI_VIDEO)
बाह्य पूर्णांक acpi_video_रेजिस्टर(व्योम);
बाह्य व्योम acpi_video_unरेजिस्टर(व्योम);
बाह्य पूर्णांक acpi_video_get_edid(काष्ठा acpi_device *device, पूर्णांक type,
			       पूर्णांक device_id, व्योम **edid);
बाह्य क्रमागत acpi_backlight_type acpi_video_get_backlight_type(व्योम);
बाह्य व्योम acpi_video_set_dmi_backlight_type(क्रमागत acpi_backlight_type type);
/*
 * Note: The value वापसed by acpi_video_handles_brightness_key_presses()
 * may change over समय and should not be cached.
 */
बाह्य bool acpi_video_handles_brightness_key_presses(व्योम);
बाह्य पूर्णांक acpi_video_get_levels(काष्ठा acpi_device *device,
				 काष्ठा acpi_video_device_brightness **dev_br,
				 पूर्णांक *pmax_level);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_video_रेजिस्टर(व्योम) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम acpi_video_unरेजिस्टर(व्योम) अणु वापस; पूर्ण
अटल अंतरभूत पूर्णांक acpi_video_get_edid(काष्ठा acpi_device *device, पूर्णांक type,
				      पूर्णांक device_id, व्योम **edid)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत क्रमागत acpi_backlight_type acpi_video_get_backlight_type(व्योम)
अणु
	वापस acpi_backlight_venकरोr;
पूर्ण
अटल अंतरभूत व्योम acpi_video_set_dmi_backlight_type(क्रमागत acpi_backlight_type type)
अणु
पूर्ण
अटल अंतरभूत bool acpi_video_handles_brightness_key_presses(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_video_get_levels(काष्ठा acpi_device *device,
			काष्ठा acpi_video_device_brightness **dev_br,
			पूर्णांक *pmax_level)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
