<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VIDEO_ATAFB_H
#घोषणा _VIDEO_ATAFB_H

व्योम atafb_mfb_copyarea(काष्ठा fb_info *info, u_दीर्घ next_line, पूर्णांक sy, पूर्णांक sx, पूर्णांक dy,
			पूर्णांक dx, पूर्णांक height, पूर्णांक width);
व्योम atafb_mfb_fillrect(काष्ठा fb_info *info, u_दीर्घ next_line, u32 color,
			पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width);
व्योम atafb_mfb_linefill(काष्ठा fb_info *info, u_दीर्घ next_line,
			पूर्णांक dy, पूर्णांक dx, u32 width,
			स्थिर u8 *data, u32 bgcolor, u32 fgcolor);

व्योम atafb_iplan2p2_copyarea(काष्ठा fb_info *info, u_दीर्घ next_line, पूर्णांक sy, पूर्णांक sx, पूर्णांक dy,
			     पूर्णांक dx, पूर्णांक height, पूर्णांक width);
व्योम atafb_iplan2p2_fillrect(काष्ठा fb_info *info, u_दीर्घ next_line, u32 color,
			     पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width);
व्योम atafb_iplan2p2_linefill(काष्ठा fb_info *info, u_दीर्घ next_line,
			     पूर्णांक dy, पूर्णांक dx, u32 width,
			     स्थिर u8 *data, u32 bgcolor, u32 fgcolor);

व्योम atafb_iplan2p4_copyarea(काष्ठा fb_info *info, u_दीर्घ next_line, पूर्णांक sy, पूर्णांक sx, पूर्णांक dy,
			     पूर्णांक dx, पूर्णांक height, पूर्णांक width);
व्योम atafb_iplan2p4_fillrect(काष्ठा fb_info *info, u_दीर्घ next_line, u32 color,
			     पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width);
व्योम atafb_iplan2p4_linefill(काष्ठा fb_info *info, u_दीर्घ next_line,
			     पूर्णांक dy, पूर्णांक dx, u32 width,
			     स्थिर u8 *data, u32 bgcolor, u32 fgcolor);

व्योम atafb_iplan2p8_copyarea(काष्ठा fb_info *info, u_दीर्घ next_line, पूर्णांक sy, पूर्णांक sx, पूर्णांक dy,
			     पूर्णांक dx, पूर्णांक height, पूर्णांक width);
व्योम atafb_iplan2p8_fillrect(काष्ठा fb_info *info, u_दीर्घ next_line, u32 color,
			     पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width);
व्योम atafb_iplan2p8_linefill(काष्ठा fb_info *info, u_दीर्घ next_line,
			     पूर्णांक dy, पूर्णांक dx, u32 width,
			     स्थिर u8 *data, u32 bgcolor, u32 fgcolor);

#पूर्ण_अगर /* _VIDEO_ATAFB_H */
