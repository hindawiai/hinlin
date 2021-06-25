<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
** यंत्र/bootinfo-mac.h -- Macपूर्णांकosh-specअगरic boot inक्रमmation definitions
*/

#अगर_अघोषित _UAPI_ASM_M68K_BOOTINFO_MAC_H
#घोषणा _UAPI_ASM_M68K_BOOTINFO_MAC_H


    /*
     *  Macपूर्णांकosh-specअगरic tags (all __be32)
     */

#घोषणा BI_MAC_MODEL		0x8000	/* Mac Gestalt ID (model type) */
#घोषणा BI_MAC_VADDR		0x8001	/* Mac video base address */
#घोषणा BI_MAC_VDEPTH		0x8002	/* Mac video depth */
#घोषणा BI_MAC_VROW		0x8003	/* Mac video rowbytes */
#घोषणा BI_MAC_VDIM		0x8004	/* Mac video dimensions */
#घोषणा BI_MAC_VLOGICAL		0x8005	/* Mac video logical base */
#घोषणा BI_MAC_SCCBASE		0x8006	/* Mac SCC base address */
#घोषणा BI_MAC_BTIME		0x8007	/* Mac boot समय */
#घोषणा BI_MAC_GMTBIAS		0x8008	/* Mac GMT समयzone offset */
#घोषणा BI_MAC_MEMSIZE		0x8009	/* Mac RAM size (sanity check) */
#घोषणा BI_MAC_CPUID		0x800a	/* Mac CPU type (sanity check) */
#घोषणा BI_MAC_ROMBASE		0x800b	/* Mac प्रणाली ROM base address */


    /*
     *  Macपूर्णांकosh hardware profile data - unused, see macपूर्णांकosh.h क्रम
     *  reasonable type values
     */

#घोषणा BI_MAC_VIA1BASE		0x8010	/* Mac VIA1 base address (always present) */
#घोषणा BI_MAC_VIA2BASE		0x8011	/* Mac VIA2 base address (type varies) */
#घोषणा BI_MAC_VIA2TYPE		0x8012	/* Mac VIA2 type (VIA, RBV, OSS) */
#घोषणा BI_MAC_ADBTYPE		0x8013	/* Mac ADB पूर्णांकerface type */
#घोषणा BI_MAC_ASCBASE		0x8014	/* Mac Apple Sound Chip base address */
#घोषणा BI_MAC_SCSI5380		0x8015	/* Mac NCR 5380 SCSI (base address, multi) */
#घोषणा BI_MAC_SCSIDMA		0x8016	/* Mac SCSI DMA (base address) */
#घोषणा BI_MAC_SCSI5396		0x8017	/* Mac NCR 53C96 SCSI (base address, multi) */
#घोषणा BI_MAC_IDETYPE		0x8018	/* Mac IDE पूर्णांकerface type */
#घोषणा BI_MAC_IDEBASE		0x8019	/* Mac IDE पूर्णांकerface base address */
#घोषणा BI_MAC_NUBUS		0x801a	/* Mac Nubus type (none, regular, pseuकरो) */
#घोषणा BI_MAC_SLOTMASK		0x801b	/* Mac Nubus slots present */
#घोषणा BI_MAC_SCCTYPE		0x801c	/* Mac SCC serial type (normal, IOP) */
#घोषणा BI_MAC_ETHTYPE		0x801d	/* Mac builtin ethernet type (Sonic, MACE */
#घोषणा BI_MAC_ETHBASE		0x801e	/* Mac builtin ethernet base address */
#घोषणा BI_MAC_PMU		0x801f	/* Mac घातer management / घातeroff hardware */
#घोषणा BI_MAC_IOP_SWIM		0x8020	/* Mac SWIM floppy IOP */
#घोषणा BI_MAC_IOP_ADB		0x8021	/* Mac ADB IOP */


    /*
     * Macपूर्णांकosh Gestalt numbers (BI_MAC_MODEL)
     */

#घोषणा MAC_MODEL_II		6
#घोषणा MAC_MODEL_IIX		7
#घोषणा MAC_MODEL_IICX		8
#घोषणा MAC_MODEL_SE30		9
#घोषणा MAC_MODEL_IICI		11
#घोषणा MAC_MODEL_IIFX		13	/* And well numbered it is too */
#घोषणा MAC_MODEL_IISI		18
#घोषणा MAC_MODEL_LC		19
#घोषणा MAC_MODEL_Q900		20
#घोषणा MAC_MODEL_PB170		21
#घोषणा MAC_MODEL_Q700		22
#घोषणा MAC_MODEL_CLII		23	/* aka: P200 */
#घोषणा MAC_MODEL_PB140		25
#घोषणा MAC_MODEL_Q950		26	/* aka: WGS95 */
#घोषणा MAC_MODEL_LCIII		27	/* aka: P450 */
#घोषणा MAC_MODEL_PB210		29
#घोषणा MAC_MODEL_C650		30
#घोषणा MAC_MODEL_PB230		32
#घोषणा MAC_MODEL_PB180		33
#घोषणा MAC_MODEL_PB160		34
#घोषणा MAC_MODEL_Q800		35	/* aka: WGS80 */
#घोषणा MAC_MODEL_Q650		36
#घोषणा MAC_MODEL_LCII		37	/* aka: P400/405/410/430 */
#घोषणा MAC_MODEL_PB250		38
#घोषणा MAC_MODEL_IIVI		44
#घोषणा MAC_MODEL_P600		45	/* aka: P600CD */
#घोषणा MAC_MODEL_IIVX		48
#घोषणा MAC_MODEL_CCL		49	/* aka: P250 */
#घोषणा MAC_MODEL_PB165C	50
#घोषणा MAC_MODEL_C610		52	/* aka: WGS60 */
#घोषणा MAC_MODEL_Q610		53
#घोषणा MAC_MODEL_PB145		54	/* aka: PB145B */
#घोषणा MAC_MODEL_P520		56	/* aka: LC520 */
#घोषणा MAC_MODEL_C660		60
#घोषणा MAC_MODEL_P460		62	/* aka: LCIII+, P466/P467 */
#घोषणा MAC_MODEL_PB180C	71
#घोषणा MAC_MODEL_PB520		72	/* aka: PB520C, PB540, PB540C, PB550C */
#घोषणा MAC_MODEL_PB270C	77
#घोषणा MAC_MODEL_Q840		78
#घोषणा MAC_MODEL_P550		80	/* aka: LC550, P560 */
#घोषणा MAC_MODEL_CCLII		83	/* aka: P275 */
#घोषणा MAC_MODEL_PB165		84
#घोषणा MAC_MODEL_PB190		85	/* aka: PB190CS */
#घोषणा MAC_MODEL_TV		88
#घोषणा MAC_MODEL_P475		89	/* aka: LC475, P476 */
#घोषणा MAC_MODEL_P475F		90	/* aka: P475 w/ FPU (no LC040) */
#घोषणा MAC_MODEL_P575		92	/* aka: LC575, P577/P578 */
#घोषणा MAC_MODEL_Q605		94
#घोषणा MAC_MODEL_Q605_ACC	95	/* Q605 accelerated to 33 MHz */
#घोषणा MAC_MODEL_Q630		98	/* aka: LC630, P630/631/635/636/637/638/640 */
#घोषणा MAC_MODEL_P588		99	/* aka: LC580, P580 */
#घोषणा MAC_MODEL_PB280		102
#घोषणा MAC_MODEL_PB280C	103
#घोषणा MAC_MODEL_PB150		115


    /*
     *  Latest Macपूर्णांकosh bootinfo version
     */

#घोषणा MAC_BOOTI_VERSION	MK_BI_VERSION(2, 0)


#पूर्ण_अगर /* _UAPI_ASM_M68K_BOOTINFO_MAC_H */
