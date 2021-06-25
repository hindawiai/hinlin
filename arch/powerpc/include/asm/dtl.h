<शैली गुरु>
#अगर_अघोषित _ASM_POWERPC_DTL_H
#घोषणा _ASM_POWERPC_DTL_H

#समावेश <यंत्र/lppaca.h>
#समावेश <linux/spinlock_types.h>

/*
 * Layout of entries in the hypervisor's dispatch trace log buffer.
 */
काष्ठा dtl_entry अणु
	u8	dispatch_reason;
	u8	preempt_reason;
	__be16	processor_id;
	__be32	enqueue_to_dispatch_समय;
	__be32	पढ़ोy_to_enqueue_समय;
	__be32	रुकोing_to_पढ़ोy_समय;
	__be64	समयbase;
	__be64	fault_addr;
	__be64	srr0;
	__be64	srr1;
पूर्ण;

#घोषणा DISPATCH_LOG_BYTES	4096	/* bytes per cpu */
#घोषणा N_DISPATCH_LOG		(DISPATCH_LOG_BYTES / माप(काष्ठा dtl_entry))

/*
 * Dispatch trace log event enable mask:
 *   0x1: voluntary भव processor रुकोs
 *   0x2: समय-slice preempts
 *   0x4: भव partition memory page faults
 */
#घोषणा DTL_LOG_CEDE		0x1
#घोषणा DTL_LOG_PREEMPT		0x2
#घोषणा DTL_LOG_FAULT		0x4
#घोषणा DTL_LOG_ALL		(DTL_LOG_CEDE | DTL_LOG_PREEMPT | DTL_LOG_FAULT)

बाह्य काष्ठा kmem_cache *dtl_cache;
बाह्य rwlock_t dtl_access_lock;

/*
 * When CONFIG_VIRT_CPU_ACCOUNTING_NATIVE = y, the cpu accounting code controls
 * पढ़ोing from the dispatch trace log.  If other code wants to consume
 * DTL entries, it can set this poपूर्णांकer to a function that will get
 * called once क्रम each DTL entry that माला_लो processed.
 */
बाह्य व्योम (*dtl_consumer)(काष्ठा dtl_entry *entry, u64 index);

बाह्य व्योम रेजिस्टर_dtl_buffer(पूर्णांक cpu);
बाह्य व्योम alloc_dtl_buffers(अचिन्हित दीर्घ *समय_limit);
बाह्य दीर्घ hcall_vphn(अचिन्हित दीर्घ cpu, u64 flags, __be32 *associativity);

#पूर्ण_अगर /* _ASM_POWERPC_DTL_H */
