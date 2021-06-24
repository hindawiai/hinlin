<शैली गुरु>
#अगर_अघोषित _LINUX_FBCON_H
#घोषणा _LINUX_FBCON_H

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE
व्योम __init fb_console_init(व्योम);
व्योम __निकास fb_console_निकास(व्योम);
पूर्णांक fbcon_fb_रेजिस्टरed(काष्ठा fb_info *info);
व्योम fbcon_fb_unरेजिस्टरed(काष्ठा fb_info *info);
व्योम fbcon_fb_unbind(काष्ठा fb_info *info);
व्योम fbcon_suspended(काष्ठा fb_info *info);
व्योम fbcon_resumed(काष्ठा fb_info *info);
पूर्णांक fbcon_mode_deleted(काष्ठा fb_info *info,
		       काष्ठा fb_videomode *mode);
व्योम fbcon_new_modelist(काष्ठा fb_info *info);
व्योम fbcon_get_requirement(काष्ठा fb_info *info,
			   काष्ठा fb_blit_caps *caps);
व्योम fbcon_fb_blanked(काष्ठा fb_info *info, पूर्णांक blank);
व्योम fbcon_update_vcs(काष्ठा fb_info *info, bool all);
व्योम fbcon_remap_all(काष्ठा fb_info *info);
पूर्णांक fbcon_set_con2fb_map_ioctl(व्योम __user *argp);
पूर्णांक fbcon_get_con2fb_map_ioctl(व्योम __user *argp);
#अन्यथा
अटल अंतरभूत व्योम fb_console_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम fb_console_निकास(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक fbcon_fb_रेजिस्टरed(काष्ठा fb_info *info) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम fbcon_fb_unरेजिस्टरed(काष्ठा fb_info *info) अणुपूर्ण
अटल अंतरभूत व्योम fbcon_fb_unbind(काष्ठा fb_info *info) अणुपूर्ण
अटल अंतरभूत व्योम fbcon_suspended(काष्ठा fb_info *info) अणुपूर्ण
अटल अंतरभूत व्योम fbcon_resumed(काष्ठा fb_info *info) अणुपूर्ण
अटल अंतरभूत पूर्णांक fbcon_mode_deleted(काष्ठा fb_info *info,
				     काष्ठा fb_videomode *mode) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम fbcon_new_modelist(काष्ठा fb_info *info) अणुपूर्ण
अटल अंतरभूत व्योम fbcon_get_requirement(काष्ठा fb_info *info,
					 काष्ठा fb_blit_caps *caps) अणुपूर्ण
अटल अंतरभूत व्योम fbcon_fb_blanked(काष्ठा fb_info *info, पूर्णांक blank) अणुपूर्ण
अटल अंतरभूत व्योम fbcon_update_vcs(काष्ठा fb_info *info, bool all) अणुपूर्ण
अटल अंतरभूत व्योम fbcon_remap_all(काष्ठा fb_info *info) अणुपूर्ण
अटल अंतरभूत पूर्णांक fbcon_set_con2fb_map_ioctl(व्योम __user *argp) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक fbcon_get_con2fb_map_ioctl(व्योम __user *argp) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_FBCON_H */
