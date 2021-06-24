<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_HWRPB_H
#घोषणा __ALPHA_HWRPB_H

#घोषणा INIT_HWRPB ((काष्ठा hwrpb_काष्ठा *) 0x10000000)

/*
 * DEC processor types क्रम Alpha प्रणालीs.  Found in HWRPB.
 * These values are architected.
 */

#घोषणा EV3_CPU                 1       /* EV3                  */
#घोषणा EV4_CPU                 2       /* EV4 (21064)          */
#घोषणा LCA4_CPU                4       /* LCA4 (21066/21068)   */
#घोषणा EV5_CPU                 5       /* EV5 (21164)          */
#घोषणा EV45_CPU                6       /* EV4.5 (21064/xxx)    */
#घोषणा EV56_CPU		7	/* EV5.6 (21164)	*/
#घोषणा EV6_CPU			8	/* EV6 (21264)		*/
#घोषणा PCA56_CPU		9	/* PCA56 (21164PC)	*/
#घोषणा PCA57_CPU		10	/* PCA57 (notyet)	*/
#घोषणा EV67_CPU		11	/* EV67 (21264A)	*/
#घोषणा EV68CB_CPU		12	/* EV68CB (21264C)	*/
#घोषणा EV68AL_CPU		13	/* EV68AL (21264B)	*/
#घोषणा EV68CX_CPU		14	/* EV68CX (21264D)	*/
#घोषणा EV7_CPU			15	/* EV7 (21364)		*/
#घोषणा EV79_CPU		16	/* EV79 (21364??)	*/
#घोषणा EV69_CPU		17	/* EV69 (21264/EV69A)	*/

/*
 * DEC प्रणाली types क्रम Alpha प्रणालीs.  Found in HWRPB.
 * These values are architected.
 */

#घोषणा ST_ADU			  1	/* Alpha ADU systype	*/
#घोषणा ST_DEC_4000		  2	/* Cobra systype	*/
#घोषणा ST_DEC_7000		  3	/* Ruby systype		*/
#घोषणा ST_DEC_3000_500		  4	/* Flamingo systype	*/
#घोषणा ST_DEC_2000_300		  6	/* Jensen systype	*/
#घोषणा ST_DEC_3000_300		  7	/* Pelican systype	*/
#घोषणा ST_DEC_2100_A500	  9	/* Sable systype	*/
#घोषणा ST_DEC_AXPVME_64	 10	/* AXPvme प्रणाली type	*/
#घोषणा ST_DEC_AXPPCI_33	 11	/* NoName प्रणाली type	*/
#घोषणा ST_DEC_TLASER		 12	/* Turbolaser systype	*/
#घोषणा ST_DEC_2100_A50		 13	/* Avanti systype	*/
#घोषणा ST_DEC_MUSTANG		 14	/* Mustang systype	*/
#घोषणा ST_DEC_ALCOR		 15	/* Alcor (EV5) systype	*/
#घोषणा ST_DEC_1000		 17	/* Mikasa systype	*/
#घोषणा ST_DEC_EB64		 18	/* EB64 systype		*/
#घोषणा ST_DEC_EB66		 19	/* EB66 systype		*/
#घोषणा ST_DEC_EB64P		 20	/* EB64+ systype	*/
#घोषणा ST_DEC_BURNS		 21	/* laptop systype	*/
#घोषणा ST_DEC_RAWHIDE		 22	/* Rawhide systype	*/
#घोषणा ST_DEC_K2		 23	/* K2 systype		*/
#घोषणा ST_DEC_LYNX		 24	/* Lynx systype		*/
#घोषणा ST_DEC_XL		 25	/* Alpha XL systype	*/
#घोषणा ST_DEC_EB164		 26	/* EB164 systype	*/
#घोषणा ST_DEC_NORITAKE		 27	/* Noritake systype	*/
#घोषणा ST_DEC_CORTEX		 28	/* Cortex systype	*/
#घोषणा ST_DEC_MIATA		 30	/* Miata systype        */
#घोषणा ST_DEC_XXM		 31	/* XXM systype		*/
#घोषणा ST_DEC_TAKARA		 32	/* Takara systype	*/
#घोषणा ST_DEC_YUKON		 33	/* Yukon systype	*/
#घोषणा ST_DEC_TSUNAMI		 34	/* Tsunami systype	*/
#घोषणा ST_DEC_WILDFIRE		 35	/* Wildfire systype	*/
#घोषणा ST_DEC_CUSCO		 36	/* CUSCO systype	*/
#घोषणा ST_DEC_EIGER		 37	/* Eiger systype	*/
#घोषणा ST_DEC_TITAN		 38	/* Titan systype	*/
#घोषणा ST_DEC_MARVEL		 39	/* Marvel systype	*/

/* UNOFFICIAL!!! */
#घोषणा ST_UNOFFICIAL_BIAS	100
#घोषणा ST_DTI_RUFFIAN		101	/* RUFFIAN systype	*/

/* Alpha Processor, Inc. प्रणालीs */
#घोषणा ST_API_BIAS		200
#घोषणा ST_API_NAUTILUS		201	/* UP1000 systype	*/

काष्ठा pcb_काष्ठा अणु
	अचिन्हित दीर्घ ksp;
	अचिन्हित दीर्घ usp;
	अचिन्हित दीर्घ ptbr;
	अचिन्हित पूर्णांक pcc;
	अचिन्हित पूर्णांक asn;
	अचिन्हित दीर्घ unique;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ res1, res2;
पूर्ण;

काष्ठा percpu_काष्ठा अणु
	अचिन्हित दीर्घ hwpcb[16];
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pal_mem_size;
	अचिन्हित दीर्घ pal_scratch_size;
	अचिन्हित दीर्घ pal_mem_pa;
	अचिन्हित दीर्घ pal_scratch_pa;
	अचिन्हित दीर्घ pal_revision;
	अचिन्हित दीर्घ type;
	अचिन्हित दीर्घ variation;
	अचिन्हित दीर्घ revision;
	अचिन्हित दीर्घ serial_no[2];
	अचिन्हित दीर्घ logout_area_pa;
	अचिन्हित दीर्घ logout_area_len;
	अचिन्हित दीर्घ halt_PCBB;
	अचिन्हित दीर्घ halt_PC;
	अचिन्हित दीर्घ halt_PS;
	अचिन्हित दीर्घ halt_arg;
	अचिन्हित दीर्घ halt_ra;
	अचिन्हित दीर्घ halt_pv;
	अचिन्हित दीर्घ halt_reason;
	अचिन्हित दीर्घ res;
	अचिन्हित दीर्घ ipc_buffer[21];
	अचिन्हित दीर्घ palcode_avail[16];
	अचिन्हित दीर्घ compatibility;
	अचिन्हित दीर्घ console_data_log_pa;
	अचिन्हित दीर्घ console_data_log_length;
	अचिन्हित दीर्घ bcache_info;
पूर्ण;

काष्ठा procdesc_काष्ठा अणु
	अचिन्हित दीर्घ weird_vms_stuff;
	अचिन्हित दीर्घ address;
पूर्ण;

काष्ठा vf_map_काष्ठा अणु
	अचिन्हित दीर्घ va;
	अचिन्हित दीर्घ pa;
	अचिन्हित दीर्घ count;
पूर्ण;

काष्ठा crb_काष्ठा अणु
	काष्ठा procdesc_काष्ठा * dispatch_va;
	काष्ठा procdesc_काष्ठा * dispatch_pa;
	काष्ठा procdesc_काष्ठा * fixup_va;
	काष्ठा procdesc_काष्ठा * fixup_pa;
	/* भव->physical map */
	अचिन्हित दीर्घ map_entries;
	अचिन्हित दीर्घ map_pages;
	काष्ठा vf_map_काष्ठा map[1];
पूर्ण;

काष्ठा memclust_काष्ठा अणु
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ numpages;
	अचिन्हित दीर्घ numtested;
	अचिन्हित दीर्घ biपंचांगap_va;
	अचिन्हित दीर्घ biपंचांगap_pa;
	अचिन्हित दीर्घ biपंचांगap_chksum;
	अचिन्हित दीर्घ usage;
पूर्ण;

काष्ठा memdesc_काष्ठा अणु
	अचिन्हित दीर्घ chksum;
	अचिन्हित दीर्घ optional_pa;
	अचिन्हित दीर्घ numclusters;
	काष्ठा memclust_काष्ठा cluster[0];
पूर्ण;

काष्ठा dsr_काष्ठा अणु
	दीर्घ smm;			/* SMM nubber used by LMF       */
	अचिन्हित दीर्घ  lurt_off;	/* offset to LURT table         */
	अचिन्हित दीर्घ  sysname_off;	/* offset to sysname अक्षर count */
पूर्ण;

काष्ठा hwrpb_काष्ठा अणु
	अचिन्हित दीर्घ phys_addr;	/* check: physical address of the hwrpb */
	अचिन्हित दीर्घ id;		/* check: "HWRPB\0\0\0" */
	अचिन्हित दीर्घ revision;	
	अचिन्हित दीर्घ size;		/* size of hwrpb */
	अचिन्हित दीर्घ cpuid;
	अचिन्हित दीर्घ pagesize;		/* 8192, I hope */
	अचिन्हित दीर्घ pa_bits;		/* number of physical address bits */
	अचिन्हित दीर्घ max_asn;
	अचिन्हित अक्षर ssn[16];		/* प्रणाली serial number: big bother is watching */
	अचिन्हित दीर्घ sys_type;
	अचिन्हित दीर्घ sys_variation;
	अचिन्हित दीर्घ sys_revision;
	अचिन्हित दीर्घ पूर्णांकr_freq;	/* पूर्णांकerval घड़ी frequency * 4096 */
	अचिन्हित दीर्घ cycle_freq;	/* cycle counter frequency */
	अचिन्हित दीर्घ vptb;		/* Virtual Page Table Base address */
	अचिन्हित दीर्घ res1;
	अचिन्हित दीर्घ tbhb_offset;	/* Translation Buffer Hपूर्णांक Block */
	अचिन्हित दीर्घ nr_processors;
	अचिन्हित दीर्घ processor_size;
	अचिन्हित दीर्घ processor_offset;
	अचिन्हित दीर्घ ctb_nr;
	अचिन्हित दीर्घ ctb_size;		/* console terminal block size */
	अचिन्हित दीर्घ ctbt_offset;	/* console terminal block table offset */
	अचिन्हित दीर्घ crb_offset;	/* console callback routine block */
	अचिन्हित दीर्घ mddt_offset;	/* memory data descriptor table */
	अचिन्हित दीर्घ cdb_offset;	/* configuration data block (or शून्य) */
	अचिन्हित दीर्घ frut_offset;	/* FRU table (or शून्य) */
	व्योम (*save_terminal)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ save_terminal_data;
	व्योम (*restore_terminal)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ restore_terminal_data;
	व्योम (*CPU_restart)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ CPU_restart_data;
	अचिन्हित दीर्घ res2;
	अचिन्हित दीर्घ res3;
	अचिन्हित दीर्घ chksum;
	अचिन्हित दीर्घ rxrdy;
	अचिन्हित दीर्घ txrdy;
	अचिन्हित दीर्घ dsr_offset;	/* "Dynamic System Recognition Data Block Table" */
पूर्ण;

#अगर_घोषित __KERNEL__

बाह्य काष्ठा hwrpb_काष्ठा *hwrpb;

अटल अंतरभूत व्योम
hwrpb_update_checksum(काष्ठा hwrpb_काष्ठा *h)
अणु
	अचिन्हित दीर्घ sum = 0, *l;
        क्रम (l = (अचिन्हित दीर्घ *) h; l < (अचिन्हित दीर्घ *) &h->chksum; ++l)
                sum += *l;
        h->chksum = sum;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_HWRPB_H */
