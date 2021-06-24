<शैली गुरु>
#अगर_अघोषित __NOUVEAU_SVM_H__
#घोषणा __NOUVEAU_SVM_H__
#समावेश <nvअगर/os.h>
#समावेश <linux/mmu_notअगरier.h>
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा nouveau_drm;

काष्ठा nouveau_svmm अणु
	काष्ठा mmu_notअगरier notअगरier;
	काष्ठा nouveau_vmm *vmm;
	काष्ठा अणु
		अचिन्हित दीर्घ start;
		अचिन्हित दीर्घ limit;
	पूर्ण unmanaged;

	काष्ठा mutex mutex;
पूर्ण;

#अगर IS_ENABLED(CONFIG_DRM_NOUVEAU_SVM)
व्योम nouveau_svm_init(काष्ठा nouveau_drm *);
व्योम nouveau_svm_fini(काष्ठा nouveau_drm *);
व्योम nouveau_svm_suspend(काष्ठा nouveau_drm *);
व्योम nouveau_svm_resume(काष्ठा nouveau_drm *);

पूर्णांक nouveau_svmm_init(काष्ठा drm_device *, व्योम *, काष्ठा drm_file *);
व्योम nouveau_svmm_fini(काष्ठा nouveau_svmm **);
पूर्णांक nouveau_svmm_join(काष्ठा nouveau_svmm *, u64 inst);
व्योम nouveau_svmm_part(काष्ठा nouveau_svmm *, u64 inst);
पूर्णांक nouveau_svmm_bind(काष्ठा drm_device *, व्योम *, काष्ठा drm_file *);

व्योम nouveau_svmm_invalidate(काष्ठा nouveau_svmm *svmm, u64 start, u64 limit);
u64 *nouveau_pfns_alloc(अचिन्हित दीर्घ npages);
व्योम nouveau_pfns_मुक्त(u64 *pfns);
व्योम nouveau_pfns_map(काष्ठा nouveau_svmm *svmm, काष्ठा mm_काष्ठा *mm,
		      अचिन्हित दीर्घ addr, u64 *pfns, अचिन्हित दीर्घ npages);
#अन्यथा /* IS_ENABLED(CONFIG_DRM_NOUVEAU_SVM) */
अटल अंतरभूत व्योम nouveau_svm_init(काष्ठा nouveau_drm *drm) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_svm_fini(काष्ठा nouveau_drm *drm) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_svm_suspend(काष्ठा nouveau_drm *drm) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_svm_resume(काष्ठा nouveau_drm *drm) अणुपूर्ण

अटल अंतरभूत पूर्णांक nouveau_svmm_init(काष्ठा drm_device *device, व्योम *p,
				    काष्ठा drm_file *file)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम nouveau_svmm_fini(काष्ठा nouveau_svmm **svmmp) अणुपूर्ण

अटल अंतरभूत पूर्णांक nouveau_svmm_join(काष्ठा nouveau_svmm *svmm, u64 inst)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nouveau_svmm_part(काष्ठा nouveau_svmm *svmm, u64 inst) अणुपूर्ण

अटल अंतरभूत पूर्णांक nouveau_svmm_bind(काष्ठा drm_device *device, व्योम *p,
				    काष्ठा drm_file *file)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_DRM_NOUVEAU_SVM) */
#पूर्ण_अगर
