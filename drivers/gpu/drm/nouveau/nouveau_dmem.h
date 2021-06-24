<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित __NOUVEAU_DMEM_H__
#घोषणा __NOUVEAU_DMEM_H__
#समावेश <nvअगर/os.h>
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा nouveau_drm;
काष्ठा nouveau_svmm;
काष्ठा hmm_range;

#अगर IS_ENABLED(CONFIG_DRM_NOUVEAU_SVM)
व्योम nouveau_dmem_init(काष्ठा nouveau_drm *);
व्योम nouveau_dmem_fini(काष्ठा nouveau_drm *);
व्योम nouveau_dmem_suspend(काष्ठा nouveau_drm *);
व्योम nouveau_dmem_resume(काष्ठा nouveau_drm *);

पूर्णांक nouveau_dmem_migrate_vma(काष्ठा nouveau_drm *drm,
			     काष्ठा nouveau_svmm *svmm,
			     काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ start,
			     अचिन्हित दीर्घ end);
अचिन्हित दीर्घ nouveau_dmem_page_addr(काष्ठा page *page);

#अन्यथा /* IS_ENABLED(CONFIG_DRM_NOUVEAU_SVM) */
अटल अंतरभूत व्योम nouveau_dmem_init(काष्ठा nouveau_drm *drm) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_dmem_fini(काष्ठा nouveau_drm *drm) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_dmem_suspend(काष्ठा nouveau_drm *drm) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_dmem_resume(काष्ठा nouveau_drm *drm) अणुपूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_DRM_NOUVEAU_SVM) */
#पूर्ण_अगर
