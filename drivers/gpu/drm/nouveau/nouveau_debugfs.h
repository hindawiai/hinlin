<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_DEBUGFS_H__
#घोषणा __NOUVEAU_DEBUGFS_H__

#समावेश <drm/drm_debugfs.h>

#अगर defined(CONFIG_DEBUG_FS)

#समावेश "nouveau_drv.h"

काष्ठा nouveau_debugfs अणु
	काष्ठा nvअगर_object ctrl;
पूर्ण;

अटल अंतरभूत काष्ठा nouveau_debugfs *
nouveau_debugfs(काष्ठा drm_device *dev)
अणु
	वापस nouveau_drm(dev)->debugfs;
पूर्ण

बाह्य व्योम  nouveau_drm_debugfs_init(काष्ठा drm_minor *);
बाह्य पूर्णांक  nouveau_debugfs_init(काष्ठा nouveau_drm *);
बाह्य व्योम nouveau_debugfs_fini(काष्ठा nouveau_drm *);
#अन्यथा
अटल अंतरभूत व्योम
nouveau_drm_debugfs_init(काष्ठा drm_minor *minor)
अणुपूर्ण

अटल अंतरभूत पूर्णांक
nouveau_debugfs_init(काष्ठा nouveau_drm *drm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
nouveau_debugfs_fini(काष्ठा nouveau_drm *drm)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
