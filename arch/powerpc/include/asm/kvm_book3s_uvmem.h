<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_KVM_BOOK3S_UVMEM_H__
#घोषणा __ASM_KVM_BOOK3S_UVMEM_H__

#अगर_घोषित CONFIG_PPC_UV
पूर्णांक kvmppc_uvmem_init(व्योम);
व्योम kvmppc_uvmem_मुक्त(व्योम);
bool kvmppc_uvmem_available(व्योम);
पूर्णांक kvmppc_uvmem_slot_init(काष्ठा kvm *kvm, स्थिर काष्ठा kvm_memory_slot *slot);
व्योम kvmppc_uvmem_slot_मुक्त(काष्ठा kvm *kvm,
			    स्थिर काष्ठा kvm_memory_slot *slot);
अचिन्हित दीर्घ kvmppc_h_svm_page_in(काष्ठा kvm *kvm,
				   अचिन्हित दीर्घ gra,
				   अचिन्हित दीर्घ flags,
				   अचिन्हित दीर्घ page_shअगरt);
अचिन्हित दीर्घ kvmppc_h_svm_page_out(काष्ठा kvm *kvm,
				    अचिन्हित दीर्घ gra,
				    अचिन्हित दीर्घ flags,
				    अचिन्हित दीर्घ page_shअगरt);
अचिन्हित दीर्घ kvmppc_h_svm_init_start(काष्ठा kvm *kvm);
अचिन्हित दीर्घ kvmppc_h_svm_init_करोne(काष्ठा kvm *kvm);
पूर्णांक kvmppc_send_page_to_uv(काष्ठा kvm *kvm, अचिन्हित दीर्घ gfn);
अचिन्हित दीर्घ kvmppc_h_svm_init_पात(काष्ठा kvm *kvm);
व्योम kvmppc_uvmem_drop_pages(स्थिर काष्ठा kvm_memory_slot *मुक्त,
			     काष्ठा kvm *kvm, bool skip_page_out);
पूर्णांक kvmppc_uvmem_memslot_create(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *new);
व्योम kvmppc_uvmem_memslot_delete(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *old);
#अन्यथा
अटल अंतरभूत पूर्णांक kvmppc_uvmem_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kvmppc_uvmem_मुक्त(व्योम) अणु पूर्ण

अटल अंतरभूत bool kvmppc_uvmem_available(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
kvmppc_uvmem_slot_init(काष्ठा kvm *kvm, स्थिर काष्ठा kvm_memory_slot *slot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
kvmppc_uvmem_slot_मुक्त(काष्ठा kvm *kvm, स्थिर काष्ठा kvm_memory_slot *slot) अणु पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
kvmppc_h_svm_page_in(काष्ठा kvm *kvm, अचिन्हित दीर्घ gra,
		     अचिन्हित दीर्घ flags, अचिन्हित दीर्घ page_shअगरt)
अणु
	वापस H_UNSUPPORTED;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
kvmppc_h_svm_page_out(काष्ठा kvm *kvm, अचिन्हित दीर्घ gra,
		      अचिन्हित दीर्घ flags, अचिन्हित दीर्घ page_shअगरt)
अणु
	वापस H_UNSUPPORTED;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvmppc_h_svm_init_start(काष्ठा kvm *kvm)
अणु
	वापस H_UNSUPPORTED;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvmppc_h_svm_init_करोne(काष्ठा kvm *kvm)
अणु
	वापस H_UNSUPPORTED;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvmppc_h_svm_init_पात(काष्ठा kvm *kvm)
अणु
	वापस H_UNSUPPORTED;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_send_page_to_uv(काष्ठा kvm *kvm, अचिन्हित दीर्घ gfn)
अणु
	वापस -EFAULT;
पूर्ण

अटल अंतरभूत व्योम
kvmppc_uvmem_drop_pages(स्थिर काष्ठा kvm_memory_slot *मुक्त,
			काष्ठा kvm *kvm, bool skip_page_out) अणु पूर्ण

अटल अंतरभूत पूर्णांक  kvmppc_uvmem_memslot_create(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *new)
अणु
	वापस H_UNSUPPORTED;
पूर्ण

अटल अंतरभूत व्योम  kvmppc_uvmem_memslot_delete(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *old) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_UV */
#पूर्ण_अगर /* __ASM_KVM_BOOK3S_UVMEM_H__ */
