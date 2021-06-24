<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
*                  QLOGIC LINUX SOFTWARE
*
* QLogic  QLA1280 (Ultra2)  and  QLA12160 (Ultra3) SCSI driver
* Copyright (C) 2000 Qlogic Corporation (www.qlogic.com)
* Copyright (C) 2001-2004 Jes Sorensen, Wild Open Source Inc.
* Copyright (C) 2003-2004 Christoph Hellwig
*
******************************************************************************/
#घोषणा QLA1280_VERSION      "3.27.1"
/*****************************************************************************
    Revision History:
    Rev  3.27.1, February 8, 2010, Michael Reed
	- Retain firmware image क्रम error recovery.
    Rev  3.27, February 10, 2009, Michael Reed
	- General code cleanup.
	- Improve error recovery.
    Rev  3.26, January 16, 2006 Jes Sorensen
	- Ditch all < 2.6 support
    Rev  3.25.1, February 10, 2005 Christoph Hellwig
	- use pci_map_single to map non-S/G requests
	- हटाओ qla1280_proc_info
    Rev  3.25, September 28, 2004, Christoph Hellwig
	- add support क्रम ISP1020/1040
	- करोn't include "scsi.h" anymore क्रम 2.6.x
    Rev  3.24.4 June 7, 2004 Christoph Hellwig
	- reकाष्ठाure firmware loading, cleanup initialization code
	- prepare support क्रम ISP1020/1040 chips
    Rev  3.24.3 January 19, 2004, Jes Sorensen
	- Handle PCI DMA mask settings correctly
	- Correct order of error handling in probe_one, मुक्त_irq should not
	  be called अगर request_irq failed
    Rev  3.24.2 January 19, 2004, James Bottomley & Andrew Vasquez
	- Big endian fixes (James)
	- Remove bogus IOCB content on zero data transfer commands (Andrew)
    Rev  3.24.1 January 5, 2004, Jes Sorensen
	- Initialize completion queue to aव्योम OOPS on probe
	- Handle पूर्णांकerrupts during mailbox testing
    Rev  3.24 November 17, 2003, Christoph Hellwig
    	- use काष्ठा list_head क्रम completion queue
	- aव्योम old Scsi_FOO प्रकारs
	- cleanup 2.4 compat glue a bit
	- use <scsi/scsi_*.h> headers on 2.6 instead of "scsi.h"
	- make initialization क्रम memory mapped vs port I/O more similar
	- हटाओ broken pci config space manipulation
	- समाप्त more cruft
	- this is an almost perfect 2.6 scsi driver now! ;)
    Rev  3.23.39 December 17, 2003, Jes Sorensen
	- Delete completion queue from srb अगर mailbox command failed to
	  to aव्योम qla1280_करोne completeting qla1280_error_action's
	  obsolete context
	- Reduce arguments क्रम qla1280_करोne
    Rev  3.23.38 October 18, 2003, Christoph Hellwig
	- Convert to new-style hotplugable driver क्रम 2.6
	- Fix missing scsi_unरेजिस्टर/scsi_host_put on HBA removal
	- Kill some more cruft
    Rev  3.23.37 October 1, 2003, Jes Sorensen
	- Make MMIO depend on CONFIG_X86_VISWS instead of yet another
	  अक्रमom CONFIG option
	- Clean up locking in probe path
    Rev  3.23.36 October 1, 2003, Christoph Hellwig
	- queuecommand only ever receives new commands - clear flags
	- Reपूर्णांकegrate lost fixes from Linux 2.5
    Rev  3.23.35 August 14, 2003, Jes Sorensen
	- Build against 2.6
    Rev  3.23.34 July 23, 2003, Jes Sorensen
	- Remove poपूर्णांकless TRUE/FALSE macros
	- Clean up vchan handling
    Rev  3.23.33 July 3, 2003, Jes Sorensen
	- Don't define रेजिस्टर access macros beक्रमe define determining MMIO.
	  This just happened to work out on ia64 but not अन्यथाwhere.
	- Don't try and पढ़ो from the card जबतक it is in reset as
	  it won't respond and causes an MCA
    Rev  3.23.32 June 23, 2003, Jes Sorensen
	- Basic support क्रम boot समय arguments
    Rev  3.23.31 June 8, 2003, Jes Sorensen
	- Reduce boot समय messages
    Rev  3.23.30 June 6, 2003, Jes Sorensen
	- Do not enable sync/wide/ppr beक्रमe it has been determined
	  that the target device actually supports it
	- Enable DMA arbitration क्रम multi channel controllers
    Rev  3.23.29 June 3, 2003, Jes Sorensen
	- Port to 2.5.69
    Rev  3.23.28 June 3, 2003, Jes Sorensen
	- Eliminate duplicate marker commands on bus resets
	- Handle outstanding commands appropriately on bus/device resets
    Rev  3.23.27 May 28, 2003, Jes Sorensen
	- Remove bogus input queue code, let the Linux SCSI layer करो the work
	- Clean up NVRAM handling, only पढ़ो it once from the card
	- Add a number of missing शेष nvram parameters
    Rev  3.23.26 Beta May 28, 2003, Jes Sorensen
	- Use completion queue क्रम mailbox commands instead of busy रुको
    Rev  3.23.25 Beta May 27, 2003, James Bottomley
	- Migrate to use new error handling code
    Rev  3.23.24 Beta May 21, 2003, James Bottomley
	- Big endian support
	- Cleanup data direction code
    Rev  3.23.23 Beta May 12, 2003, Jes Sorensen
	- Switch to using MMIO instead of PIO
    Rev  3.23.22 Beta April 15, 2003, Jes Sorensen
	- Fix PCI parity problem with 12160 during reset.
    Rev  3.23.21 Beta April 14, 2003, Jes Sorensen
	- Use pci_map_page()/pci_unmap_page() instead of map_single version.
    Rev  3.23.20 Beta April 9, 2003, Jes Sorensen
	- Remove < 2.4.x support
	- Introduce HOST_LOCK to make the spin lock changes portable.
	- Remove a bunch of idiotic and unnecessary प्रकार's
	- Kill all leftovers of target-mode support which never worked anyway
    Rev  3.23.19 Beta April 11, 2002, Linus Torvalds
	- Do qla1280_pci_config() beक्रमe calling request_irq() and
	  request_region()
	- Use pci_dma_hi32() to handle upper word of DMA addresses instead
	  of large shअगरts
	- Hand correct arguments to मुक्त_irq() in हाल of failure
    Rev  3.23.18 Beta April 11, 2002, Jes Sorensen
	- Run source through Lindent and clean up the output
    Rev  3.23.17 Beta April 11, 2002, Jes Sorensen
	- Update SCSI firmware to qla1280 v8.15.00 and qla12160 v10.04.32
    Rev  3.23.16 Beta March 19, 2002, Jes Sorensen
	- Rely on mailbox commands generating पूर्णांकerrupts - करो not
	  run qla1280_isr() from ql1280_mailbox_command()
	- Remove device_reg_t
	- Integrate ql12160_set_target_parameters() with 1280 version
	- Make qla1280_setup() non अटल
	- Do not call qla1280_check_क्रम_dead_scsi_bus() on every I/O request
	  sent to the card - this command छोड़ोs the firmware!!!
    Rev  3.23.15 Beta March 19, 2002, Jes Sorensen
	- Clean up qla1280.h - हटाओ obsolete QL_DEBUG_LEVEL_x definitions
	- Remove a pile of poपूर्णांकless and confusing (srb_t **) and
	  (scsi_lu_t *) typecasts
	- Explicit mark that we करो not use the new error handling (क्रम now)
	- Remove scsi_qla_host_t and use 'struct' instead
	- Remove in_पात, watchकरोg_enabled, dpc, dpc_sched, bios_enabled,
	  pci_64bit_slot flags which weren't used क्रम anything anyway
	- Grab host->host_lock जबतक calling qla1280_isr() from पात()
	- Use spin_lock()/spin_unlock() in qla1280_पूर्णांकr_handler() - we
	  करो not need to save/restore flags in the पूर्णांकerrupt handler
	- Enable पूर्णांकerrupts early (beक्रमe any mailbox access) in preparation
	  क्रम cleaning up the mailbox handling
    Rev  3.23.14 Beta March 14, 2002, Jes Sorensen
	- Further cleanups. Remove all trace of QL_DEBUG_LEVEL_x and replace
	  it with proper use of dprपूर्णांकk().
	- Make qla1280_prपूर्णांक_scsi_cmd() and qla1280_dump_buffer() both take
	  a debug level argument to determine अगर data is to be prपूर्णांकed
	- Add KERN_* info to prपूर्णांकk()
    Rev  3.23.13 Beta March 14, 2002, Jes Sorensen
	- Signअगरicant cosmetic cleanups
	- Change debug code to use dprपूर्णांकk() and हटाओ #अगर mess
    Rev  3.23.12 Beta March 13, 2002, Jes Sorensen
	- More cosmetic cleanups, fix places treating वापस as function
	- use cpu_relax() in qla1280_debounce_रेजिस्टर()
    Rev  3.23.11 Beta March 13, 2002, Jes Sorensen
	- Make it compile under 2.5.5
    Rev  3.23.10 Beta October 1, 2001, Jes Sorensen
	- Do no typecast लघु * to दीर्घ * in QL1280BoardTbl, this
	  broke miserably on big endian boxes
    Rev  3.23.9 Beta September 30, 2001, Jes Sorensen
	- Remove pre 2.2 hack क्रम checking क्रम reentrance in पूर्णांकerrupt handler
	- Make data types used to receive from SCSI_अणुBUS,TCN,LUNपूर्ण_32
	  अचिन्हित पूर्णांक to match the types from काष्ठा scsi_cmnd
    Rev  3.23.8 Beta September 29, 2001, Jes Sorensen
	- Remove bogus समयr_t प्रकार from qla1280.h
	- Remove obsolete pre 2.2 PCI setup code, use proper #घोषणा's
	  क्रम PCI_ values, call pci_set_master()
	- Fix memleak of qla1280_buffer on module unload
	- Only compile module parsing code #अगर_घोषित MODULE - should be
	  changed to use inभागidual MODULE_PARM's later
	- Remove dummy_buffer that was never modअगरied nor prपूर्णांकed
	- ENTER()/LEAVE() are noops unless QL_DEBUG_LEVEL_3, hence हटाओ
	  #अगर_घोषित QL_DEBUG_LEVEL_3/#पूर्ण_अगर around ENTER()/LEAVE() calls
	- Remove \ल from prपूर्णांक statements, this is Linux, not DOS
	- Remove obsolete QLA1280_अणुSCSILU,INTR,RINGपूर्ण_अणुLOCK,UNLOCKपूर्ण
	  dummy macros
	- Remove C++ compile hack in header file as Linux driver are not
	  supposed to be compiled as C++
	- Kill MS_64BITS macro as it makes the code more पढ़ोable
	- Remove unnecessary flags.in_पूर्णांकerrupts bit
    Rev  3.23.7 Beta August 20, 2001, Jes Sorensen
	- Dont' check क्रम set flags on q->q_flag one by one in qla1280_next()
        - Check whether the पूर्णांकerrupt was generated by the QLA1280 beक्रमe
          करोing any processing
	- qla1280_status_entry(): Only zero out part of sense_buffer that
	  is not being copied पूर्णांकo
	- Remove more superflouous typecasts
	- qla1280_32bit_start_scsi() replace home-brew स_नकल() with स_नकल()
    Rev  3.23.6 Beta August 20, 2001, Tony Luck, Intel
        - Don't walk the entire list in qla1280_putq_t() just to directly
	  grab the poपूर्णांकer to the last element afterwards
    Rev  3.23.5 Beta August 9, 2001, Jes Sorensen
	- Don't use IRQF_DISABLED, it's use is deprecated क्रम this kinda driver
    Rev  3.23.4 Beta August 8, 2001, Jes Sorensen
	- Set dev->max_sectors to 1024
    Rev  3.23.3 Beta August 6, 2001, Jes Sorensen
	- Provide compat macros क्रम pci_enable_device(), pci_find_subsys()
	  and scsi_set_pci_device()
	- Call scsi_set_pci_device() क्रम all devices
	- Reduce size of kernel version dependent device probe code
	- Move duplicate probe/init code to separate function
	- Handle error अगर qla1280_mem_alloc() fails
	- Kill OFFSET() macro and use Linux's PCI definitions instead
        - Kill निजी काष्ठाure defining PCI config space (काष्ठा config_reg)
	- Only allocate I/O port region अगर not in MMIO mode
	- Remove duplicate (unused) sanity check of sअगरe of srb_t
    Rev  3.23.2 Beta August 6, 2001, Jes Sorensen
	- Change home-brew स_रखो() implementations to use स_रखो()
        - Remove all references to COMTRACE() - accessing a PC's COM2 serial
          port directly is not legal under Linux.
    Rev  3.23.1 Beta April 24, 2001, Jes Sorensen
        - Remove pre 2.2 kernel support
        - clean up 64 bit DMA setting to use 2.4 API (provide backwards compat)
        - Fix MMIO access to use पढ़ोl/ग_लिखोl instead of directly
          dereferencing poपूर्णांकers
        - Nuke MSDOS debugging code
        - Change true/false data types to पूर्णांक from uपूर्णांक8_t
        - Use पूर्णांक क्रम counters instead of uपूर्णांक8_t etc.
        - Clean up size & byte order conversion macro usage
    Rev  3.23 Beta January 11, 2001 BN Qlogic
        - Added check of device_id when handling non
          QLA12160s during detect().
    Rev  3.22 Beta January 5, 2001 BN Qlogic
        - Changed queue_task() to schedule_task()
          क्रम kernels 2.4.0 and higher.
          Note: 2.4.0-testxx kernels released prior to
                the actual 2.4.0 kernel release on January 2001
                will get compile/link errors with schedule_task().
                Please update your kernel to released 2.4.0 level,
                or comment lines in this file flagged with  3.22
                to resolve compile/link error of schedule_task().
        - Added -DCONFIG_SMP in addition to -D__SMP__
          in Makefile क्रम 2.4.0 builds of driver as module.
    Rev  3.21 Beta January 4, 2001 BN Qlogic
        - Changed criteria of 64/32 Bit mode of HBA
          operation according to BITS_PER_LONG rather
          than HBA's NVRAM setting of >4Gig memory bit;
          so that the HBA स्वतः-configures without the need
          to setup each प्रणाली inभागidually.
    Rev  3.20 Beta December 5, 2000 BN Qlogic
        - Added priority handling to IA-64  onboard SCSI
          ISP12160 chip क्रम kernels greater than 2.3.18.
        - Added irqrestore क्रम qla1280_पूर्णांकr_handler.
        - Enabled /proc/scsi/qla1280 पूर्णांकerface.
        - Clear /proc/scsi/qla1280 counters in detect().
    Rev  3.19 Beta October 13, 2000 BN Qlogic
        - Declare driver_ढाँचा क्रम new kernel
          (2.4.0 and greater) scsi initialization scheme.
        - Update /proc/scsi entry क्रम 2.3.18 kernels and
          above as qla1280
    Rev  3.18 Beta October 10, 2000 BN Qlogic
        - Changed scan order of adapters to map
          the QLA12160 followed by the QLA1280.
    Rev  3.17 Beta September 18, 2000 BN Qlogic
        - Removed warnings क्रम 32 bit 2.4.x compiles
        - Corrected declared size क्रम request and response
          DMA addresses that are kept in each ha
    Rev. 3.16 Beta  August 25, 2000   BN  Qlogic
        - Corrected 64 bit addressing issue on IA-64
          where the upper 32 bits were not properly
          passed to the RISC engine.
    Rev. 3.15 Beta  August 22, 2000   BN  Qlogic
        - Modअगरied qla1280_setup_chip to properly load
          ISP firmware क्रम greater that 4 Gig memory on IA-64
    Rev. 3.14 Beta  August 16, 2000   BN  Qlogic
        - Added setting of dma_mask to full 64 bit
          अगर flags.enable_64bit_addressing is set in NVRAM
    Rev. 3.13 Beta  August 16, 2000   BN  Qlogic
        - Use new PCI DMA mapping APIs क्रम 2.4.x kernel
    Rev. 3.12       July 18, 2000    Redhat & BN Qlogic
        - Added check of pci_enable_device to detect() क्रम 2.3.x
        - Use pci_resource_start() instead of
          pdev->resource[0].start in detect() क्रम 2.3.x
        - Updated driver version
    Rev. 3.11       July 14, 2000    BN  Qlogic
	- Updated SCSI Firmware to following versions:
	  qla1x80:   8.13.08
	  qla1x160:  10.04.08
	- Updated driver version to 3.11
    Rev. 3.10    June 23, 2000   BN Qlogic
        - Added filtering of AMI SubSys Venकरोr ID devices
    Rev. 3.9
        - DEBUG_QLA1280 undefined and  new version  BN Qlogic
    Rev. 3.08b      May 9, 2000    MD Dell
        - Added logic to check against AMI subप्रणाली venकरोr ID
	Rev. 3.08       May 4, 2000    DG  Qlogic
        - Added logic to check क्रम PCI subप्रणाली ID.
	Rev. 3.07       Apr 24, 2000    DG & BN  Qlogic
	   - Updated SCSI Firmware to following versions:
	     qla12160:   10.01.19
		 qla1280:     8.09.00
	Rev. 3.06       Apr 12, 2000    DG & BN  Qlogic
	   - Internal revision; not released
    Rev. 3.05       Mar 28, 2000    DG & BN  Qlogic
       - Edit correction क्रम virt_to_bus and PROC.
    Rev. 3.04       Mar 28, 2000    DG & BN  Qlogic
       - Merge changes from ia64 port.
    Rev. 3.03       Mar 28, 2000    BN  Qlogic
       - Increase version to reflect new code drop with compile fix
         of issue with inclusion of linux/spinlock क्रम 2.3 kernels
    Rev. 3.02       Mar 15, 2000    BN  Qlogic
       - Merge qla1280_proc_info from 2.10 code base
    Rev. 3.01       Feb 10, 2000    BN  Qlogic
       - Corrected code to compile on a 2.2.x kernel.
    Rev. 3.00       Jan 17, 2000    DG  Qlogic
	   - Added 64-bit support.
    Rev. 2.07       Nov 9, 1999     DG  Qlogic
	   - Added new routine to set target parameters क्रम ISP12160.
    Rev. 2.06       Sept 10, 1999     DG  Qlogic
       - Added support क्रम ISP12160 Ultra 3 chip.
    Rev. 2.03       August 3, 1999    Fred Lewis, Intel DuPont
	- Modअगरied code to हटाओ errors generated when compiling with
	  Cygnus IA64 Compiler.
        - Changed conversion of poपूर्णांकers to अचिन्हित दीर्घs instead of पूर्णांकegers.
        - Changed type of I/O port variables from uपूर्णांक32_t to अचिन्हित दीर्घ.
        - Modअगरied OFFSET macro to work with 64-bit as well as 32-bit.
        - Changed प्र_लिखो and prपूर्णांकk क्रमmat specअगरiers क्रम poपूर्णांकers to %p.
        - Changed some पूर्णांक to दीर्घ type casts where needed in प्र_लिखो & prपूर्णांकk.
        - Added l modअगरiers to प्र_लिखो and prपूर्णांकk क्रमmat specअगरiers क्रम दीर्घs.
        - Removed unused local variables.
    Rev. 1.20       June 8, 1999      DG,  Qlogic
         Changes to support RedHat release 6.0 (kernel 2.2.5).
       - Added SCSI exclusive access lock (io_request_lock) when accessing
         the adapter.
       - Added changes क्रम the new LINUX पूर्णांकerface ढाँचा. Some new error
         handling routines have been added to the ढाँचा, but क्रम now we
         will use the old ones.
    -   Initial Beta Release.
*****************************************************************************/


#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pci_ids.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/types.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>


/*
 * Compile समय Options:
 *            0 - Disable and 1 - Enable
 */
#घोषणा  DEBUG_QLA1280_INTR	0
#घोषणा  DEBUG_PRINT_NVRAM	0
#घोषणा  DEBUG_QLA1280		0

#घोषणा	MEMORY_MAPPED_IO	1

#समावेश "qla1280.h"

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
#घोषणा QLA_64BIT_PTR	1
#पूर्ण_अगर

#घोषणा NVRAM_DELAY()			udelay(500)	/* 2 microseconds */

#घोषणा IS_ISP1040(ha) (ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP1020)
#घोषणा IS_ISP1x40(ha) (ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP1020 || \
			ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP1240)
#घोषणा IS_ISP1x160(ha)        (ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP10160 || \
				ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP12160)


अटल पूर्णांक qla1280_probe_one(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम qla1280_हटाओ_one(काष्ठा pci_dev *);

/*
 *  QLogic Driver Support Function Prototypes.
 */
अटल व्योम qla1280_करोne(काष्ठा scsi_qla_host *);
अटल पूर्णांक qla1280_get_token(अक्षर *);
अटल पूर्णांक qla1280_setup(अक्षर *s) __init;

/*
 *  QLogic ISP1280 Hardware Support Function Prototypes.
 */
अटल पूर्णांक qla1280_load_firmware(काष्ठा scsi_qla_host *);
अटल पूर्णांक qla1280_init_rings(काष्ठा scsi_qla_host *);
अटल पूर्णांक qla1280_nvram_config(काष्ठा scsi_qla_host *);
अटल पूर्णांक qla1280_mailbox_command(काष्ठा scsi_qla_host *,
				   uपूर्णांक8_t, uपूर्णांक16_t *);
अटल पूर्णांक qla1280_bus_reset(काष्ठा scsi_qla_host *, पूर्णांक);
अटल पूर्णांक qla1280_device_reset(काष्ठा scsi_qla_host *, पूर्णांक, पूर्णांक);
अटल पूर्णांक qla1280_पात_command(काष्ठा scsi_qla_host *, काष्ठा srb *, पूर्णांक);
अटल पूर्णांक qla1280_पात_isp(काष्ठा scsi_qla_host *);
#अगर_घोषित QLA_64BIT_PTR
अटल पूर्णांक qla1280_64bit_start_scsi(काष्ठा scsi_qla_host *, काष्ठा srb *);
#अन्यथा
अटल पूर्णांक qla1280_32bit_start_scsi(काष्ठा scsi_qla_host *, काष्ठा srb *);
#पूर्ण_अगर
अटल व्योम qla1280_nv_ग_लिखो(काष्ठा scsi_qla_host *, uपूर्णांक16_t);
अटल व्योम qla1280_poll(काष्ठा scsi_qla_host *);
अटल व्योम qla1280_reset_adapter(काष्ठा scsi_qla_host *);
अटल व्योम qla1280_marker(काष्ठा scsi_qla_host *, पूर्णांक, पूर्णांक, पूर्णांक, u8);
अटल व्योम qla1280_isp_cmd(काष्ठा scsi_qla_host *);
अटल व्योम qla1280_isr(काष्ठा scsi_qla_host *, काष्ठा list_head *);
अटल व्योम qla1280_rst_aen(काष्ठा scsi_qla_host *);
अटल व्योम qla1280_status_entry(काष्ठा scsi_qla_host *, काष्ठा response *,
				 काष्ठा list_head *);
अटल व्योम qla1280_error_entry(काष्ठा scsi_qla_host *, काष्ठा response *,
				काष्ठा list_head *);
अटल uपूर्णांक16_t qla1280_get_nvram_word(काष्ठा scsi_qla_host *, uपूर्णांक32_t);
अटल uपूर्णांक16_t qla1280_nvram_request(काष्ठा scsi_qla_host *, uपूर्णांक32_t);
अटल uपूर्णांक16_t qla1280_debounce_रेजिस्टर(अस्थिर uपूर्णांक16_t __iomem *);
अटल request_t *qla1280_req_pkt(काष्ठा scsi_qla_host *);
अटल पूर्णांक qla1280_check_क्रम_dead_scsi_bus(काष्ठा scsi_qla_host *,
					   अचिन्हित पूर्णांक);
अटल व्योम qla1280_get_target_parameters(काष्ठा scsi_qla_host *,
					   काष्ठा scsi_device *);
अटल पूर्णांक qla1280_set_target_parameters(काष्ठा scsi_qla_host *, पूर्णांक, पूर्णांक);


अटल काष्ठा qla_driver_setup driver_setup;

/*
 * convert scsi data direction to request_t control flags
 */
अटल अंतरभूत uपूर्णांक16_t
qla1280_data_direction(काष्ठा scsi_cmnd *cmnd)
अणु
	चयन(cmnd->sc_data_direction) अणु
	हाल DMA_FROM_DEVICE:
		वापस BIT_5;
	हाल DMA_TO_DEVICE:
		वापस BIT_6;
	हाल DMA_BIसूचीECTIONAL:
		वापस BIT_5 | BIT_6;
	/*
	 * We could BUG() on शेष here अगर one of the four हालs aren't
	 * met, but then again अगर we receive something like that from the
	 * SCSI layer we have more serious problems. This shuts up GCC.
	 */
	हाल DMA_NONE:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
		
#अगर DEBUG_QLA1280
अटल व्योम __qla1280_prपूर्णांक_scsi_cmd(काष्ठा scsi_cmnd * cmd);
अटल व्योम __qla1280_dump_buffer(अक्षर *, पूर्णांक);
#पूर्ण_अगर


/*
 * insmod needs to find the variable and make it poपूर्णांक to something
 */
#अगर_घोषित MODULE
अटल अक्षर *qla1280;

/* insmod qla1280 options=verbose" */
module_param(qla1280, अक्षरp, 0);
#अन्यथा
__setup("qla1280=", qla1280_setup);
#पूर्ण_अगर


/*
 * We use the scsi_poपूर्णांकer काष्ठाure that's included with each scsi_command
 * to overlay our काष्ठा srb over it. qla1280_init() checks that a srb is not
 * bigger than a scsi_poपूर्णांकer.
 */

#घोषणा	CMD_SP(Cmnd)		&Cmnd->SCp
#घोषणा	CMD_CDBLEN(Cmnd)	Cmnd->cmd_len
#घोषणा	CMD_CDBP(Cmnd)		Cmnd->cmnd
#घोषणा	CMD_SNSP(Cmnd)		Cmnd->sense_buffer
#घोषणा	CMD_SNSLEN(Cmnd)	SCSI_SENSE_BUFFERSIZE
#घोषणा	CMD_RESULT(Cmnd)	Cmnd->result
#घोषणा	CMD_HANDLE(Cmnd)	Cmnd->host_scribble
#घोषणा CMD_REQUEST(Cmnd)	Cmnd->request->cmd

#घोषणा CMD_HOST(Cmnd)		Cmnd->device->host
#घोषणा SCSI_BUS_32(Cmnd)	Cmnd->device->channel
#घोषणा SCSI_TCN_32(Cmnd)	Cmnd->device->id
#घोषणा SCSI_LUN_32(Cmnd)	Cmnd->device->lun


/*****************************************/
/*   ISP Boards supported by this driver */
/*****************************************/

काष्ठा qla_boards अणु
	अक्षर *name;		/* Board ID String */
	पूर्णांक numPorts;		/* Number of SCSI ports */
	पूर्णांक fw_index;		/* index पूर्णांकo qla1280_fw_tbl क्रम firmware */
पूर्ण;

/* NOTE: the last argument in each entry is used to index ql1280_board_tbl */
अटल काष्ठा pci_device_id qla1280_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP12160,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP1020,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1पूर्ण,
	अणुPCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP1080,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2पूर्ण,
	अणुPCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP1240,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 3पूर्ण,
	अणुPCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP1280,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4पूर्ण,
	अणुPCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_ISP10160,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 5पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, qla1280_pci_tbl);

अटल DEFINE_MUTEX(qla1280_firmware_mutex);

काष्ठा qla_fw अणु
	अक्षर *fwname;
	स्थिर काष्ठा firmware *fw;
पूर्ण;

#घोषणा QL_NUM_FW_IMAGES 3

अटल काष्ठा qla_fw qla1280_fw_tbl[QL_NUM_FW_IMAGES] = अणु
	अणु"qlogic/1040.bin",  शून्यपूर्ण,	/* image 0 */
	अणु"qlogic/1280.bin",  शून्यपूर्ण,	/* image 1 */
	अणु"qlogic/12160.bin", शून्यपूर्ण,	/* image 2 */
पूर्ण;

/* NOTE: Order of boards in this table must match order in qla1280_pci_tbl */
अटल काष्ठा qla_boards ql1280_board_tbl[] = अणु
	अणु.name = "QLA12160", .numPorts = 2, .fw_index = 2पूर्ण,
	अणु.name = "QLA1040" , .numPorts = 1, .fw_index = 0पूर्ण,
	अणु.name = "QLA1080" , .numPorts = 1, .fw_index = 1पूर्ण,
	अणु.name = "QLA1240" , .numPorts = 2, .fw_index = 1पूर्ण,
	अणु.name = "QLA1280" , .numPorts = 2, .fw_index = 1पूर्ण,
	अणु.name = "QLA10160", .numPorts = 1, .fw_index = 2पूर्ण,
	अणु.name = "        ", .numPorts = 0, .fw_index = -1पूर्ण,
पूर्ण;

अटल पूर्णांक qla1280_verbose = 1;

#अगर DEBUG_QLA1280
अटल पूर्णांक ql_debug_level = 1;
#घोषणा dprपूर्णांकk(level, क्रमmat, a...)	\
	करो अणु अगर (ql_debug_level >= level) prपूर्णांकk(KERN_ERR क्रमmat, ##a); पूर्ण जबतक(0)
#घोषणा qla1280_dump_buffer(level, buf, size)	\
	अगर (ql_debug_level >= level) __qla1280_dump_buffer(buf, size)
#घोषणा qla1280_prपूर्णांक_scsi_cmd(level, cmd)	\
	अगर (ql_debug_level >= level) __qla1280_prपूर्णांक_scsi_cmd(cmd)
#अन्यथा
#घोषणा ql_debug_level			0
#घोषणा dprपूर्णांकk(level, क्रमmat, a...)	करोअणुपूर्णजबतक(0)
#घोषणा qla1280_dump_buffer(a, b, c)	करोअणुपूर्णजबतक(0)
#घोषणा qla1280_prपूर्णांक_scsi_cmd(a, b)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर

#घोषणा ENTER(x)		dprपूर्णांकk(3, "qla1280 : Entering %s()\n", x);
#घोषणा LEAVE(x)		dprपूर्णांकk(3, "qla1280 : Leaving %s()\n", x);
#घोषणा ENTER_INTR(x)		dprपूर्णांकk(4, "qla1280 : Entering %s()\n", x);
#घोषणा LEAVE_INTR(x)		dprपूर्णांकk(4, "qla1280 : Leaving %s()\n", x);


अटल पूर्णांक qla1280_पढ़ो_nvram(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t *wptr;
	uपूर्णांक8_t chksum;
	पूर्णांक cnt, i;
	काष्ठा nvram *nv;

	ENTER("qla1280_read_nvram");

	अगर (driver_setup.no_nvram)
		वापस 1;

	prपूर्णांकk(KERN_INFO "scsi(%ld): Reading NVRAM\n", ha->host_no);

	wptr = (uपूर्णांक16_t *)&ha->nvram;
	nv = &ha->nvram;
	chksum = 0;
	क्रम (cnt = 0; cnt < 3; cnt++) अणु
		*wptr = qla1280_get_nvram_word(ha, cnt);
		chksum += *wptr & 0xff;
		chksum += (*wptr >> 8) & 0xff;
		wptr++;
	पूर्ण

	अगर (nv->id0 != 'I' || nv->id1 != 'S' ||
	    nv->id2 != 'P' || nv->id3 != ' ' || nv->version < 1) अणु
		dprपूर्णांकk(2, "Invalid nvram ID or version!\n");
		chksum = 1;
	पूर्ण अन्यथा अणु
		क्रम (; cnt < माप(काष्ठा nvram); cnt++) अणु
			*wptr = qla1280_get_nvram_word(ha, cnt);
			chksum += *wptr & 0xff;
			chksum += (*wptr >> 8) & 0xff;
			wptr++;
		पूर्ण
	पूर्ण

	dprपूर्णांकk(3, "qla1280_read_nvram: NVRAM Magic ID= %c %c %c %02x"
	       " version %i\n", nv->id0, nv->id1, nv->id2, nv->id3,
	       nv->version);


	अगर (chksum) अणु
		अगर (!driver_setup.no_nvram)
			prपूर्णांकk(KERN_WARNING "scsi(%ld): Unable to identify or "
			       "validate NVRAM checksum, using default "
			       "settings\n", ha->host_no);
		ha->nvram_valid = 0;
	पूर्ण अन्यथा
		ha->nvram_valid = 1;

	/* The firmware पूर्णांकerface is, um, पूर्णांकeresting, in that the
	 * actual firmware image on the chip is little endian, thus,
	 * the process of taking that image to the CPU would end up
	 * little endian.  However, the firmware पूर्णांकerface requires it
	 * to be पढ़ो a word (two bytes) at a समय.
	 *
	 * The net result of this would be that the word (and
	 * द्विगुनword) quantities in the firmware would be correct, but
	 * the bytes would be pairwise reversed.  Since most of the
	 * firmware quantities are, in fact, bytes, we करो an extra
	 * le16_to_cpu() in the firmware पढ़ो routine.
	 *
	 * The upshot of all this is that the bytes in the firmware
	 * are in the correct places, but the 16 and 32 bit quantities
	 * are still in little endian क्रमmat.  We fix that up below by
	 * करोing extra reverses on them */
	nv->isp_parameter = cpu_to_le16(nv->isp_parameter);
	nv->firmware_feature.w = cpu_to_le16(nv->firmware_feature.w);
	क्रम(i = 0; i < MAX_BUSES; i++) अणु
		nv->bus[i].selection_समयout = cpu_to_le16(nv->bus[i].selection_समयout);
		nv->bus[i].max_queue_depth = cpu_to_le16(nv->bus[i].max_queue_depth);
	पूर्ण
	dprपूर्णांकk(1, "qla1280_read_nvram: Completed Reading NVRAM\n");
	LEAVE("qla1280_read_nvram");

	वापस chksum;
पूर्ण

/**************************************************************************
 *   qla1280_info
 *     Return a string describing the driver.
 **************************************************************************/
अटल स्थिर अक्षर *
qla1280_info(काष्ठा Scsi_Host *host)
अणु
	अटल अक्षर qla1280_scsi_name_buffer[125];
	अक्षर *bp;
	काष्ठा scsi_qla_host *ha;
	काष्ठा qla_boards *bdp;

	bp = &qla1280_scsi_name_buffer[0];
	ha = (काष्ठा scsi_qla_host *)host->hostdata;
	bdp = &ql1280_board_tbl[ha->devnum];
	स_रखो(bp, 0, माप(qla1280_scsi_name_buffer));

	प्र_लिखो (bp,
		 "QLogic %s PCI to SCSI Host Adapter\n"
		 "       Firmware version: %2d.%02d.%02d, Driver version %s",
		 &bdp->name[0], ha->fwver1, ha->fwver2, ha->fwver3,
		 QLA1280_VERSION);
	वापस bp;
पूर्ण

/**************************************************************************
 *   qla1280_queuecommand
 *     Queue a command to the controller.
 *
 * Note:
 * The mid-level driver tries to ensures that queuecommand never माला_लो invoked
 * concurrently with itself or the पूर्णांकerrupt handler (although the
 * पूर्णांकerrupt handler may call this routine as part of request-completion
 * handling).   Unक्रमtunately, it someबार calls the scheduler in पूर्णांकerrupt
 * context which is a big NO! NO!.
 **************************************************************************/
अटल पूर्णांक
qla1280_queuecommand_lck(काष्ठा scsi_cmnd *cmd, व्योम (*fn)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा scsi_qla_host *ha = (काष्ठा scsi_qla_host *)host->hostdata;
	काष्ठा srb *sp = (काष्ठा srb *)CMD_SP(cmd);
	पूर्णांक status;

	cmd->scsi_करोne = fn;
	sp->cmd = cmd;
	sp->flags = 0;
	sp->रुको = शून्य;
	CMD_HANDLE(cmd) = (अचिन्हित अक्षर *)शून्य;

	qla1280_prपूर्णांक_scsi_cmd(5, cmd);

#अगर_घोषित QLA_64BIT_PTR
	/*
	 * Using 64 bit commands अगर the PCI bridge करोesn't support it is a
	 * bit wasteful, however this should really only happen अगर one's
	 * PCI controller is completely broken, like the BCM1250. For
	 * sane hardware this is not an issue.
	 */
	status = qla1280_64bit_start_scsi(ha, sp);
#अन्यथा
	status = qla1280_32bit_start_scsi(ha, sp);
#पूर्ण_अगर
	वापस status;
पूर्ण

अटल DEF_SCSI_QCMD(qla1280_queuecommand)

क्रमागत action अणु
	ABORT_COMMAND,
	DEVICE_RESET,
	BUS_RESET,
	ADAPTER_RESET,
पूर्ण;


अटल व्योम qla1280_mailbox_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा scsi_qla_host *ha = from_समयr(ha, t, mailbox_समयr);
	काष्ठा device_reg __iomem *reg;
	reg = ha->iobase;

	ha->mailbox_out[0] = RD_REG_WORD(&reg->mailbox0);
	prपूर्णांकk(KERN_ERR "scsi(%ld): mailbox timed out, mailbox0 %04x, "
	       "ictrl %04x, istatus %04x\n", ha->host_no, ha->mailbox_out[0],
	       RD_REG_WORD(&reg->ictrl), RD_REG_WORD(&reg->istatus));
	complete(ha->mailbox_रुको);
पूर्ण

अटल पूर्णांक
_qla1280_रुको_क्रम_single_command(काष्ठा scsi_qla_host *ha, काष्ठा srb *sp,
				 काष्ठा completion *रुको)
अणु
	पूर्णांक	status = FAILED;
	काष्ठा scsi_cmnd *cmd = sp->cmd;

	spin_unlock_irq(ha->host->host_lock);
	रुको_क्रम_completion_समयout(रुको, 4*HZ);
	spin_lock_irq(ha->host->host_lock);
	sp->रुको = शून्य;
	अगर(CMD_HANDLE(cmd) == COMPLETED_HANDLE) अणु
		status = SUCCESS;
		(*cmd->scsi_करोne)(cmd);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक
qla1280_रुको_क्रम_single_command(काष्ठा scsi_qla_host *ha, काष्ठा srb *sp)
अणु
	DECLARE_COMPLETION_ONSTACK(रुको);

	sp->रुको = &रुको;
	वापस _qla1280_रुको_क्रम_single_command(ha, sp, &रुको);
पूर्ण

अटल पूर्णांक
qla1280_रुको_क्रम_pending_commands(काष्ठा scsi_qla_host *ha, पूर्णांक bus, पूर्णांक target)
अणु
	पूर्णांक		cnt;
	पूर्णांक		status;
	काष्ठा srb	*sp;
	काष्ठा scsi_cmnd *cmd;

	status = SUCCESS;

	/*
	 * Wait क्रम all commands with the designated bus/target
	 * to be completed by the firmware
	 */
	क्रम (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS; cnt++) अणु
		sp = ha->outstanding_cmds[cnt];
		अगर (sp) अणु
			cmd = sp->cmd;

			अगर (bus >= 0 && SCSI_BUS_32(cmd) != bus)
				जारी;
			अगर (target >= 0 && SCSI_TCN_32(cmd) != target)
				जारी;

			status = qla1280_रुको_क्रम_single_command(ha, sp);
			अगर (status == FAILED)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**************************************************************************
 * qla1280_error_action
 *    The function will attempt to perक्रमm a specअगरied error action and
 *    रुको क्रम the results (or समय out).
 *
 * Input:
 *      cmd = Linux SCSI command packet of the command that cause the
 *            bus reset.
 *      action = error action to take (see action_t)
 *
 * Returns:
 *      SUCCESS or FAILED
 *
 **************************************************************************/
अटल पूर्णांक
qla1280_error_action(काष्ठा scsi_cmnd *cmd, क्रमागत action action)
अणु
	काष्ठा scsi_qla_host *ha;
	पूर्णांक bus, target, lun;
	काष्ठा srb *sp;
	पूर्णांक i, found;
	पूर्णांक result=FAILED;
	पूर्णांक रुको_क्रम_bus=-1;
	पूर्णांक रुको_क्रम_target = -1;
	DECLARE_COMPLETION_ONSTACK(रुको);

	ENTER("qla1280_error_action");

	ha = (काष्ठा scsi_qla_host *)(CMD_HOST(cmd)->hostdata);
	sp = (काष्ठा srb *)CMD_SP(cmd);
	bus = SCSI_BUS_32(cmd);
	target = SCSI_TCN_32(cmd);
	lun = SCSI_LUN_32(cmd);

	dprपूर्णांकk(4, "error_action %i, istatus 0x%04x\n", action,
		RD_REG_WORD(&ha->iobase->istatus));

	dprपूर्णांकk(4, "host_cmd 0x%04x, ictrl 0x%04x, jiffies %li\n",
		RD_REG_WORD(&ha->iobase->host_cmd),
		RD_REG_WORD(&ha->iobase->ictrl), jअगरfies);

	अगर (qla1280_verbose)
		prपूर्णांकk(KERN_INFO "scsi(%li): Resetting Cmnd=0x%p, "
		       "Handle=0x%p, action=0x%x\n",
		       ha->host_no, cmd, CMD_HANDLE(cmd), action);

	/*
	 * Check to see अगर we have the command in the outstanding_cmds[]
	 * array.  If not then it must have completed beक्रमe this error
	 * action was initiated.  If the error_action isn't ABORT_COMMAND
	 * then the driver must proceed with the requested action.
	 */
	found = -1;
	क्रम (i = 0; i < MAX_OUTSTANDING_COMMANDS; i++) अणु
		अगर (sp == ha->outstanding_cmds[i]) अणु
			found = i;
			sp->रुको = &रुको; /* we'll रुको क्रम it to complete */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found < 0) अणु	/* driver करोesn't have command */
		result = SUCCESS;
		अगर (qla1280_verbose) अणु
			prपूर्णांकk(KERN_INFO
			       "scsi(%ld:%d:%d:%d): specified command has "
			       "already completed.\n", ha->host_no, bus,
				target, lun);
		पूर्ण
	पूर्ण

	चयन (action) अणु

	हाल ABORT_COMMAND:
		dprपूर्णांकk(1, "qla1280: RISC aborting command\n");
		/*
		 * The पात might fail due to race when the host_lock
		 * is released to issue the पात.  As such, we
		 * करोn't bother to check the वापस status.
		 */
		अगर (found >= 0)
			qla1280_पात_command(ha, sp, found);
		अवरोध;

	हाल DEVICE_RESET:
		अगर (qla1280_verbose)
			prपूर्णांकk(KERN_INFO
			       "scsi(%ld:%d:%d:%d): Queueing device reset "
			       "command.\n", ha->host_no, bus, target, lun);
		अगर (qla1280_device_reset(ha, bus, target) == 0) अणु
			/* issued device reset, set रुको conditions */
			रुको_क्रम_bus = bus;
			रुको_क्रम_target = target;
		पूर्ण
		अवरोध;

	हाल BUS_RESET:
		अगर (qla1280_verbose)
			prपूर्णांकk(KERN_INFO "qla1280(%ld:%d): Issued bus "
			       "reset.\n", ha->host_no, bus);
		अगर (qla1280_bus_reset(ha, bus) == 0) अणु
			/* issued bus reset, set रुको conditions */
			रुको_क्रम_bus = bus;
		पूर्ण
		अवरोध;

	हाल ADAPTER_RESET:
	शेष:
		अगर (qla1280_verbose) अणु
			prपूर्णांकk(KERN_INFO
			       "scsi(%ld): Issued ADAPTER RESET\n",
			       ha->host_no);
			prपूर्णांकk(KERN_INFO "scsi(%ld): I/O processing will "
			       "continue automatically\n", ha->host_no);
		पूर्ण
		ha->flags.reset_active = 1;

		अगर (qla1280_पात_isp(ha) != 0) अणु	/* it's dead */
			result = FAILED;
		पूर्ण

		ha->flags.reset_active = 0;
	पूर्ण

	/*
	 * At this poपूर्णांक, the host_lock has been released and retaken
	 * by the issuance of the mailbox command.
	 * Wait क्रम the command passed in by the mid-layer अगर it
	 * was found by the driver.  It might have been वापसed
	 * between eh recovery steps, hence the check of the "found"
	 * variable.
	 */

	अगर (found >= 0)
		result = _qla1280_रुको_क्रम_single_command(ha, sp, &रुको);

	अगर (action == ABORT_COMMAND && result != SUCCESS) अणु
		prपूर्णांकk(KERN_WARNING
		       "scsi(%li:%i:%i:%i): "
		       "Unable to abort command!\n",
		       ha->host_no, bus, target, lun);
	पूर्ण

	/*
	 * If the command passed in by the mid-layer has been
	 * वापसed by the board, then रुको क्रम any additional
	 * commands which are supposed to complete based upon
	 * the error action.
	 *
	 * All commands are unconditionally वापसed during a
	 * call to qla1280_पात_isp(), ADAPTER_RESET.  No need
	 * to रुको क्रम them.
	 */
	अगर (result == SUCCESS && रुको_क्रम_bus >= 0) अणु
		result = qla1280_रुको_क्रम_pending_commands(ha,
					रुको_क्रम_bus, रुको_क्रम_target);
	पूर्ण

	dprपूर्णांकk(1, "RESET returning %d\n", result);

	LEAVE("qla1280_error_action");
	वापस result;
पूर्ण

/**************************************************************************
 *   qla1280_पात
 *     Abort the specअगरied SCSI command(s).
 **************************************************************************/
अटल पूर्णांक
qla1280_eh_पात(काष्ठा scsi_cmnd * cmd)
अणु
	पूर्णांक rc;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = qla1280_error_action(cmd, ABORT_COMMAND);
	spin_unlock_irq(cmd->device->host->host_lock);

	वापस rc;
पूर्ण

/**************************************************************************
 *   qla1280_device_reset
 *     Reset the specअगरied SCSI device
 **************************************************************************/
अटल पूर्णांक
qla1280_eh_device_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक rc;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = qla1280_error_action(cmd, DEVICE_RESET);
	spin_unlock_irq(cmd->device->host->host_lock);

	वापस rc;
पूर्ण

/**************************************************************************
 *   qla1280_bus_reset
 *     Reset the specअगरied bus.
 **************************************************************************/
अटल पूर्णांक
qla1280_eh_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक rc;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = qla1280_error_action(cmd, BUS_RESET);
	spin_unlock_irq(cmd->device->host->host_lock);

	वापस rc;
पूर्ण

/**************************************************************************
 *   qla1280_adapter_reset
 *     Reset the specअगरied adapter (both channels)
 **************************************************************************/
अटल पूर्णांक
qla1280_eh_adapter_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक rc;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = qla1280_error_action(cmd, ADAPTER_RESET);
	spin_unlock_irq(cmd->device->host->host_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक
qla1280_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		  sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads, sectors, cylinders;

	heads = 64;
	sectors = 32;
	cylinders = (अचिन्हित दीर्घ)capacity / (heads * sectors);
	अगर (cylinders > 1024) अणु
		heads = 255;
		sectors = 63;
		cylinders = (अचिन्हित दीर्घ)capacity / (heads * sectors);
		/* अगर (cylinders > 1023)
		   cylinders = 1023; */
	पूर्ण

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	वापस 0;
पूर्ण

 
/* disable risc and host पूर्णांकerrupts */
अटल अंतरभूत व्योम
qla1280_disable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	WRT_REG_WORD(&ha->iobase->ictrl, 0);
	RD_REG_WORD(&ha->iobase->ictrl);	/* PCI Posted Write flush */
पूर्ण

/* enable risc and host पूर्णांकerrupts */
अटल अंतरभूत व्योम
qla1280_enable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	WRT_REG_WORD(&ha->iobase->ictrl, (ISP_EN_INT | ISP_EN_RISC));
	RD_REG_WORD(&ha->iobase->ictrl);	/* PCI Posted Write flush */
पूर्ण

/**************************************************************************
 * qla1280_पूर्णांकr_handler
 *   Handles the H/W पूर्णांकerrupt
 **************************************************************************/
अटल irqवापस_t
qla1280_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha;
	काष्ठा device_reg __iomem *reg;
	u16 data;
	पूर्णांक handled = 0;

	ENTER_INTR ("qla1280_intr_handler");
	ha = (काष्ठा scsi_qla_host *)dev_id;

	spin_lock(ha->host->host_lock);

	ha->isr_count++;
	reg = ha->iobase;

	qla1280_disable_पूर्णांकrs(ha);

	data = qla1280_debounce_रेजिस्टर(&reg->istatus);
	/* Check क्रम pending पूर्णांकerrupts. */
	अगर (data & RISC_INT) अणु	
		qla1280_isr(ha, &ha->करोne_q);
		handled = 1;
	पूर्ण
	अगर (!list_empty(&ha->करोne_q))
		qla1280_करोne(ha);

	spin_unlock(ha->host->host_lock);

	qla1280_enable_पूर्णांकrs(ha);

	LEAVE_INTR("qla1280_intr_handler");
	वापस IRQ_RETVAL(handled);
पूर्ण


अटल पूर्णांक
qla1280_set_target_parameters(काष्ठा scsi_qla_host *ha, पूर्णांक bus, पूर्णांक target)
अणु
	uपूर्णांक8_t mr;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	काष्ठा nvram *nv;
	पूर्णांक status, lun;

	nv = &ha->nvram;

	mr = BIT_3 | BIT_2 | BIT_1 | BIT_0;

	/* Set Target Parameters. */
	mb[0] = MBC_SET_TARGET_PARAMETERS;
	mb[1] = (uपूर्णांक16_t)((bus ? target | BIT_7 : target) << 8);
	mb[2] = nv->bus[bus].target[target].parameter.renegotiate_on_error << 8;
	mb[2] |= nv->bus[bus].target[target].parameter.stop_queue_on_check << 9;
	mb[2] |= nv->bus[bus].target[target].parameter.स्वतः_request_sense << 10;
	mb[2] |= nv->bus[bus].target[target].parameter.tag_queuing << 11;
	mb[2] |= nv->bus[bus].target[target].parameter.enable_sync << 12;
	mb[2] |= nv->bus[bus].target[target].parameter.enable_wide << 13;
	mb[2] |= nv->bus[bus].target[target].parameter.parity_checking << 14;
	mb[2] |= nv->bus[bus].target[target].parameter.disconnect_allowed << 15;

	अगर (IS_ISP1x160(ha)) अणु
		mb[2] |= nv->bus[bus].target[target].ppr_1x160.flags.enable_ppr << 5;
		mb[3] =	(nv->bus[bus].target[target].flags.flags1x160.sync_offset << 8);
		mb[6] =	(nv->bus[bus].target[target].ppr_1x160.flags.ppr_options << 8) |
			 nv->bus[bus].target[target].ppr_1x160.flags.ppr_bus_width;
		mr |= BIT_6;
	पूर्ण अन्यथा अणु
		mb[3] =	(nv->bus[bus].target[target].flags.flags1x80.sync_offset << 8);
	पूर्ण
	mb[3] |= nv->bus[bus].target[target].sync_period;

	status = qla1280_mailbox_command(ha, mr, mb);

	/* Set Device Queue Parameters. */
	क्रम (lun = 0; lun < MAX_LUNS; lun++) अणु
		mb[0] = MBC_SET_DEVICE_QUEUE;
		mb[1] = (uपूर्णांक16_t)((bus ? target | BIT_7 : target) << 8);
		mb[1] |= lun;
		mb[2] = nv->bus[bus].max_queue_depth;
		mb[3] = nv->bus[bus].target[target].execution_throttle;
		status |= qla1280_mailbox_command(ha, 0x0f, mb);
	पूर्ण

	अगर (status)
		prपूर्णांकk(KERN_WARNING "scsi(%ld:%i:%i): "
		       "qla1280_set_target_parameters() failed\n",
		       ha->host_no, bus, target);
	वापस status;
पूर्ण


/**************************************************************************
 *   qla1280_slave_configure
 *
 * Description:
 *   Determines the queue depth क्रम a given device.  There are two ways
 *   a queue depth can be obtained क्रम a tagged queueing device.  One
 *   way is the शेष queue depth which is determined by whether
 *   If it is defined, then it is used
 *   as the शेष queue depth.  Otherwise, we use either 4 or 8 as the
 *   शेष queue depth (dependent on the number of hardware SCBs).
 **************************************************************************/
अटल पूर्णांक
qla1280_slave_configure(काष्ठा scsi_device *device)
अणु
	काष्ठा scsi_qla_host *ha;
	पूर्णांक शेष_depth = 3;
	पूर्णांक bus = device->channel;
	पूर्णांक target = device->id;
	पूर्णांक status = 0;
	काष्ठा nvram *nv;
	अचिन्हित दीर्घ flags;

	ha = (काष्ठा scsi_qla_host *)device->host->hostdata;
	nv = &ha->nvram;

	अगर (qla1280_check_क्रम_dead_scsi_bus(ha, bus))
		वापस 1;

	अगर (device->tagged_supported &&
	    (ha->bus_settings[bus].qtag_enables & (BIT_0 << target))) अणु
		scsi_change_queue_depth(device, ha->bus_settings[bus].hiwat);
	पूर्ण अन्यथा अणु
		scsi_change_queue_depth(device, शेष_depth);
	पूर्ण

	nv->bus[bus].target[target].parameter.enable_sync = device->sdtr;
	nv->bus[bus].target[target].parameter.enable_wide = device->wdtr;
	nv->bus[bus].target[target].ppr_1x160.flags.enable_ppr = device->ppr;

	अगर (driver_setup.no_sync ||
	    (driver_setup.sync_mask &&
	     (~driver_setup.sync_mask & (1 << target))))
		nv->bus[bus].target[target].parameter.enable_sync = 0;
	अगर (driver_setup.no_wide ||
	    (driver_setup.wide_mask &&
	     (~driver_setup.wide_mask & (1 << target))))
		nv->bus[bus].target[target].parameter.enable_wide = 0;
	अगर (IS_ISP1x160(ha)) अणु
		अगर (driver_setup.no_ppr ||
		    (driver_setup.ppr_mask &&
		     (~driver_setup.ppr_mask & (1 << target))))
			nv->bus[bus].target[target].ppr_1x160.flags.enable_ppr = 0;
	पूर्ण

	spin_lock_irqsave(ha->host->host_lock, flags);
	अगर (nv->bus[bus].target[target].parameter.enable_sync)
		status = qla1280_set_target_parameters(ha, bus, target);
	qla1280_get_target_parameters(ha, device);
	spin_unlock_irqrestore(ha->host->host_lock, flags);
	वापस status;
पूर्ण


/*
 * qla1280_करोne
 *      Process completed commands.
 *
 * Input:
 *      ha           = adapter block poपूर्णांकer.
 */
अटल व्योम
qla1280_करोne(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा srb *sp;
	काष्ठा list_head *करोne_q;
	पूर्णांक bus, target;
	काष्ठा scsi_cmnd *cmd;

	ENTER("qla1280_done");

	करोne_q = &ha->करोne_q;

	जबतक (!list_empty(करोne_q)) अणु
		sp = list_entry(करोne_q->next, काष्ठा srb, list);

		list_del(&sp->list);
	
		cmd = sp->cmd;
		bus = SCSI_BUS_32(cmd);
		target = SCSI_TCN_32(cmd);

		चयन ((CMD_RESULT(cmd) >> 16)) अणु
		हाल DID_RESET:
			/* Issue marker command. */
			अगर (!ha->flags.पात_isp_active)
				qla1280_marker(ha, bus, target, 0, MK_SYNC_ID);
			अवरोध;
		हाल DID_ABORT:
			sp->flags &= ~SRB_ABORT_PENDING;
			sp->flags |= SRB_ABORTED;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* Release memory used क्रम this I/O */
		scsi_dma_unmap(cmd);

		/* Call the mid-level driver पूर्णांकerrupt handler */
		ha->actthपढ़ोs--;

		अगर (sp->रुको == शून्य)
			(*(cmd)->scsi_करोne)(cmd);
		अन्यथा
			complete(sp->रुको);
	पूर्ण
	LEAVE("qla1280_done");
पूर्ण

/*
 * Translates a ISP error to a Linux SCSI error
 */
अटल पूर्णांक
qla1280_वापस_status(काष्ठा response * sts, काष्ठा scsi_cmnd *cp)
अणु
	पूर्णांक host_status = DID_ERROR;
	uपूर्णांक16_t comp_status = le16_to_cpu(sts->comp_status);
	uपूर्णांक16_t state_flags = le16_to_cpu(sts->state_flags);
	uपूर्णांक32_t residual_length = le32_to_cpu(sts->residual_length);
	uपूर्णांक16_t scsi_status = le16_to_cpu(sts->scsi_status);
#अगर DEBUG_QLA1280_INTR
	अटल अक्षर *reason[] = अणु
		"DID_OK",
		"DID_NO_CONNECT",
		"DID_BUS_BUSY",
		"DID_TIME_OUT",
		"DID_BAD_TARGET",
		"DID_ABORT",
		"DID_PARITY",
		"DID_ERROR",
		"DID_RESET",
		"DID_BAD_INTR"
	पूर्ण;
#पूर्ण_अगर				/* DEBUG_QLA1280_INTR */

	ENTER("qla1280_return_status");

#अगर DEBUG_QLA1280_INTR
	/*
	  dprपूर्णांकk(1, "qla1280_return_status: compl status = 0x%04x\n",
	  comp_status);
	*/
#पूर्ण_अगर

	चयन (comp_status) अणु
	हाल CS_COMPLETE:
		host_status = DID_OK;
		अवरोध;

	हाल CS_INCOMPLETE:
		अगर (!(state_flags & SF_GOT_BUS))
			host_status = DID_NO_CONNECT;
		अन्यथा अगर (!(state_flags & SF_GOT_TARGET))
			host_status = DID_BAD_TARGET;
		अन्यथा अगर (!(state_flags & SF_SENT_CDB))
			host_status = DID_ERROR;
		अन्यथा अगर (!(state_flags & SF_TRANSFERRED_DATA))
			host_status = DID_ERROR;
		अन्यथा अगर (!(state_flags & SF_GOT_STATUS))
			host_status = DID_ERROR;
		अन्यथा अगर (!(state_flags & SF_GOT_SENSE))
			host_status = DID_ERROR;
		अवरोध;

	हाल CS_RESET:
		host_status = DID_RESET;
		अवरोध;

	हाल CS_ABORTED:
		host_status = DID_ABORT;
		अवरोध;

	हाल CS_TIMEOUT:
		host_status = DID_TIME_OUT;
		अवरोध;

	हाल CS_DATA_OVERRUN:
		dprपूर्णांकk(2, "Data overrun 0x%x\n", residual_length);
		dprपूर्णांकk(2, "qla1280_return_status: response packet data\n");
		qla1280_dump_buffer(2, (अक्षर *)sts, RESPONSE_ENTRY_SIZE);
		host_status = DID_ERROR;
		अवरोध;

	हाल CS_DATA_UNDERRUN:
		अगर ((scsi_bufflen(cp) - residual_length) <
		    cp->underflow) अणु
			prपूर्णांकk(KERN_WARNING
			       "scsi: Underflow detected - retrying "
			       "command.\n");
			host_status = DID_ERROR;
		पूर्ण अन्यथा अणु
			scsi_set_resid(cp, residual_length);
			host_status = DID_OK;
		पूर्ण
		अवरोध;

	शेष:
		host_status = DID_ERROR;
		अवरोध;
	पूर्ण

#अगर DEBUG_QLA1280_INTR
	dprपूर्णांकk(1, "qla1280 ISP status: host status (%s) scsi status %x\n",
		reason[host_status], scsi_status);
#पूर्ण_अगर

	LEAVE("qla1280_return_status");

	वापस (scsi_status & 0xff) | (host_status << 16);
पूर्ण

/****************************************************************************/
/*                QLogic ISP1280 Hardware Support Functions.                */
/****************************************************************************/

/*
 * qla1280_initialize_adapter
 *      Initialize board.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
अटल पूर्णांक
qla1280_initialize_adapter(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा device_reg __iomem *reg;
	पूर्णांक status;
	पूर्णांक bus;
	अचिन्हित दीर्घ flags;

	ENTER("qla1280_initialize_adapter");

	/* Clear adapter flags. */
	ha->flags.online = 0;
	ha->flags.disable_host_adapter = 0;
	ha->flags.reset_active = 0;
	ha->flags.पात_isp_active = 0;

	/* TODO: implement support क्रम the 1040 nvram क्रमmat */
	अगर (IS_ISP1040(ha))
		driver_setup.no_nvram = 1;

	dprपूर्णांकk(1, "Configure PCI space for adapter...\n");

	reg = ha->iobase;

	/* Insure mailbox रेजिस्टरs are मुक्त. */
	WRT_REG_WORD(&reg->semaphore, 0);
	WRT_REG_WORD(&reg->host_cmd, HC_CLR_RISC_INT);
	WRT_REG_WORD(&reg->host_cmd, HC_CLR_HOST_INT);
	RD_REG_WORD(&reg->host_cmd);

	अगर (qla1280_पढ़ो_nvram(ha)) अणु
		dprपूर्णांकk(2, "qla1280_initialize_adapter: failed to read "
			"NVRAM\n");
	पूर्ण

	/*
	 * It's necessary to grab the spin here as qla1280_mailbox_command
	 * needs to be able to drop the lock unconditionally to रुको
	 * क्रम completion.
	 */
	spin_lock_irqsave(ha->host->host_lock, flags);

	status = qla1280_load_firmware(ha);
	अगर (status) अणु
		prपूर्णांकk(KERN_ERR "scsi(%li): initialize: pci probe failed!\n",
		       ha->host_no);
		जाओ out;
	पूर्ण

	/* Setup adapter based on NVRAM parameters. */
	dprपूर्णांकk(1, "scsi(%ld): Configure NVRAM parameters\n", ha->host_no);
	qla1280_nvram_config(ha);

	अगर (ha->flags.disable_host_adapter) अणु
		status = 1;
		जाओ out;
	पूर्ण

	status = qla1280_init_rings(ha);
	अगर (status)
		जाओ out;

	/* Issue SCSI reset, अगर we can't reset twice then bus is dead */
	क्रम (bus = 0; bus < ha->ports; bus++) अणु
		अगर (!ha->bus_settings[bus].disable_scsi_reset &&
		    qla1280_bus_reset(ha, bus) &&
		    qla1280_bus_reset(ha, bus))
			ha->bus_settings[bus].scsi_bus_dead = 1;
	पूर्ण

	ha->flags.online = 1;
 out:
	spin_unlock_irqrestore(ha->host->host_lock, flags);

	अगर (status)
		dprपूर्णांकk(2, "qla1280_initialize_adapter: **** FAILED ****\n");

	LEAVE("qla1280_initialize_adapter");
	वापस status;
पूर्ण

/*
 * qla1280_request_firmware
 *      Acquire firmware क्रम chip.  Retain in memory
 *      क्रम error recovery.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *      Poपूर्णांकer to firmware image or an error code
 *      cast to poपूर्णांकer via ERR_PTR().
 */
अटल स्थिर काष्ठा firmware *
qla1280_request_firmware(काष्ठा scsi_qla_host *ha)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;
	पूर्णांक index;
	अक्षर *fwname;

	spin_unlock_irq(ha->host->host_lock);
	mutex_lock(&qla1280_firmware_mutex);

	index = ql1280_board_tbl[ha->devnum].fw_index;
	fw = qla1280_fw_tbl[index].fw;
	अगर (fw)
		जाओ out;

	fwname = qla1280_fw_tbl[index].fwname;
	err = request_firmware(&fw, fwname, &ha->pdev->dev);

	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fwname, err);
		fw = ERR_PTR(err);
		जाओ unlock;
	पूर्ण
	अगर ((fw->size % 2) || (fw->size < 6)) अणु
		prपूर्णांकk(KERN_ERR "Invalid firmware length %zu in image \"%s\"\n",
		       fw->size, fwname);
		release_firmware(fw);
		fw = ERR_PTR(-EINVAL);
		जाओ unlock;
	पूर्ण

	qla1280_fw_tbl[index].fw = fw;

 out:
	ha->fwver1 = fw->data[0];
	ha->fwver2 = fw->data[1];
	ha->fwver3 = fw->data[2];
 unlock:
	mutex_unlock(&qla1280_firmware_mutex);
	spin_lock_irq(ha->host->host_lock);
	वापस fw;
पूर्ण

/*
 * Chip diagnostics
 *      Test chip क्रम proper operation.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success.
 */
अटल पूर्णांक
qla1280_chip_diag(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	काष्ठा device_reg __iomem *reg = ha->iobase;
	पूर्णांक status = 0;
	पूर्णांक cnt;
	uपूर्णांक16_t data;
	dprपूर्णांकk(3, "qla1280_chip_diag: testing device at 0x%p \n", &reg->id_l);

	dprपूर्णांकk(1, "scsi(%ld): Verifying chip\n", ha->host_no);

	/* Soft reset chip and रुको क्रम it to finish. */
	WRT_REG_WORD(&reg->ictrl, ISP_RESET);

	/*
	 * We can't करो a traditional PCI ग_लिखो flush here by पढ़ोing
	 * back the रेजिस्टर. The card will not respond once the reset
	 * is in action and we end up with a machine check exception
	 * instead. Nothing to करो but रुको and hope क्रम the best.
	 * A portable pci_ग_लिखो_flush(pdev) call would be very useful here.
	 */
	udelay(20);
	data = qla1280_debounce_रेजिस्टर(&reg->ictrl);
	/*
	 * Yet another QLogic gem ;-(
	 */
	क्रम (cnt = 1000000; cnt && data & ISP_RESET; cnt--) अणु
		udelay(5);
		data = RD_REG_WORD(&reg->ictrl);
	पूर्ण

	अगर (!cnt)
		जाओ fail;

	/* Reset रेजिस्टर cleared by chip reset. */
	dprपूर्णांकk(3, "qla1280_chip_diag: reset register cleared by chip reset\n");

	WRT_REG_WORD(&reg->cfg_1, 0);

	/* Reset RISC and disable BIOS which
	   allows RISC to execute out of RAM. */
	WRT_REG_WORD(&reg->host_cmd, HC_RESET_RISC |
		     HC_RELEASE_RISC | HC_DISABLE_BIOS);

	RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
	data = qla1280_debounce_रेजिस्टर(&reg->mailbox0);

	/*
	 * I *LOVE* this code!
	 */
	क्रम (cnt = 1000000; cnt && data == MBS_BUSY; cnt--) अणु
		udelay(5);
		data = RD_REG_WORD(&reg->mailbox0);
	पूर्ण

	अगर (!cnt)
		जाओ fail;

	/* Check product ID of chip */
	dprपूर्णांकk(3, "qla1280_chip_diag: Checking product ID of chip\n");

	अगर (RD_REG_WORD(&reg->mailbox1) != PROD_ID_1 ||
	    (RD_REG_WORD(&reg->mailbox2) != PROD_ID_2 &&
	     RD_REG_WORD(&reg->mailbox2) != PROD_ID_2a) ||
	    RD_REG_WORD(&reg->mailbox3) != PROD_ID_3 ||
	    RD_REG_WORD(&reg->mailbox4) != PROD_ID_4) अणु
		prपूर्णांकk(KERN_INFO "qla1280: Wrong product ID = "
		       "0x%x,0x%x,0x%x,0x%x\n",
		       RD_REG_WORD(&reg->mailbox1),
		       RD_REG_WORD(&reg->mailbox2),
		       RD_REG_WORD(&reg->mailbox3),
		       RD_REG_WORD(&reg->mailbox4));
		जाओ fail;
	पूर्ण

	/*
	 * Enable पूर्णांकs early!!!
	 */
	qla1280_enable_पूर्णांकrs(ha);

	dprपूर्णांकk(1, "qla1280_chip_diag: Checking mailboxes of chip\n");
	/* Wrap Incoming Mailboxes Test. */
	mb[0] = MBC_MAILBOX_REGISTER_TEST;
	mb[1] = 0xAAAA;
	mb[2] = 0x5555;
	mb[3] = 0xAA55;
	mb[4] = 0x55AA;
	mb[5] = 0xA5A5;
	mb[6] = 0x5A5A;
	mb[7] = 0x2525;

	status = qla1280_mailbox_command(ha, 0xff, mb);
	अगर (status)
		जाओ fail;

	अगर (mb[1] != 0xAAAA || mb[2] != 0x5555 || mb[3] != 0xAA55 ||
	    mb[4] != 0x55AA || mb[5] != 0xA5A5 || mb[6] != 0x5A5A ||
	    mb[7] != 0x2525) अणु
		prपूर्णांकk(KERN_INFO "qla1280: Failed mbox check\n");
		जाओ fail;
	पूर्ण

	dprपूर्णांकk(3, "qla1280_chip_diag: exiting normally\n");
	वापस 0;
 fail:
	dprपूर्णांकk(2, "qla1280_chip_diag: **** FAILED ****\n");
	वापस status;
पूर्ण

अटल पूर्णांक
qla1280_load_firmware_pio(काष्ठा scsi_qla_host *ha)
अणु
	/* enter with host_lock acquired */

	स्थिर काष्ठा firmware *fw;
	स्थिर __le16 *fw_data;
	uपूर्णांक16_t risc_address, risc_code_size;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT], i;
	पूर्णांक err = 0;

	fw = qla1280_request_firmware(ha);
	अगर (IS_ERR(fw))
		वापस PTR_ERR(fw);

	fw_data = (स्थिर __le16 *)&fw->data[0];
	ha->fwstart = __le16_to_cpu(fw_data[2]);

	/* Load RISC code. */
	risc_address = ha->fwstart;
	fw_data = (स्थिर __le16 *)&fw->data[6];
	risc_code_size = (fw->size - 6) / 2;

	क्रम (i = 0; i < risc_code_size; i++) अणु
		mb[0] = MBC_WRITE_RAM_WORD;
		mb[1] = risc_address + i;
		mb[2] = __le16_to_cpu(fw_data[i]);

		err = qla1280_mailbox_command(ha, BIT_0 | BIT_1 | BIT_2, mb);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "scsi(%li): Failed to load firmware\n",
					ha->host_no);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित QLA_64BIT_PTR
#घोषणा LOAD_CMD	MBC_LOAD_RAM_A64_ROM
#घोषणा DUMP_CMD	MBC_DUMP_RAM_A64_ROM
#घोषणा CMD_ARGS	(BIT_7 | BIT_6 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)
#अन्यथा
#घोषणा LOAD_CMD	MBC_LOAD_RAM
#घोषणा DUMP_CMD	MBC_DUMP_RAM
#घोषणा CMD_ARGS	(BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)
#पूर्ण_अगर

#घोषणा DUMP_IT_BACK 0		/* क्रम debug of RISC loading */
अटल पूर्णांक
qla1280_load_firmware_dma(काष्ठा scsi_qla_host *ha)
अणु
	/* enter with host_lock acquired */
	स्थिर काष्ठा firmware *fw;
	स्थिर __le16 *fw_data;
	uपूर्णांक16_t risc_address, risc_code_size;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT], cnt;
	पूर्णांक err = 0, num, i;
#अगर DUMP_IT_BACK
	uपूर्णांक8_t *sp, *tbuf;
	dma_addr_t p_tbuf;

	tbuf = dma_alloc_coherent(&ha->pdev->dev, 8000, &p_tbuf, GFP_KERNEL);
	अगर (!tbuf)
		वापस -ENOMEM;
#पूर्ण_अगर

	fw = qla1280_request_firmware(ha);
	अगर (IS_ERR(fw))
		वापस PTR_ERR(fw);

	fw_data = (स्थिर __le16 *)&fw->data[0];
	ha->fwstart = __le16_to_cpu(fw_data[2]);

	/* Load RISC code. */
	risc_address = ha->fwstart;
	fw_data = (स्थिर __le16 *)&fw->data[6];
	risc_code_size = (fw->size - 6) / 2;

	dprपूर्णांकk(1, "%s: DMA RISC code (%i) words\n",
			__func__, risc_code_size);

	num = 0;
	जबतक (risc_code_size > 0) अणु
		पूर्णांक warn __attribute__((unused)) = 0;

		cnt = 2000 >> 1;

		अगर (cnt > risc_code_size)
			cnt = risc_code_size;

		dprपूर्णांकk(2, "qla1280_setup_chip:  loading risc @ =(0x%p),"
			"%d,%d(0x%x)\n",
			fw_data, cnt, num, risc_address);
		क्रम(i = 0; i < cnt; i++)
			((__le16 *)ha->request_ring)[i] = fw_data[i];

		mb[0] = LOAD_CMD;
		mb[1] = risc_address;
		mb[4] = cnt;
		mb[3] = ha->request_dma & 0xffff;
		mb[2] = (ha->request_dma >> 16) & 0xffff;
		mb[7] = upper_32_bits(ha->request_dma) & 0xffff;
		mb[6] = upper_32_bits(ha->request_dma) >> 16;
		dprपूर्णांकk(2, "%s: op=%d  0x%p = 0x%4x,0x%4x,0x%4x,0x%4x\n",
				__func__, mb[0],
				(व्योम *)(दीर्घ)ha->request_dma,
				mb[6], mb[7], mb[2], mb[3]);
		err = qla1280_mailbox_command(ha, CMD_ARGS, mb);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "scsi(%li): Failed to load partial "
			       "segment of f\n", ha->host_no);
			जाओ out;
		पूर्ण

#अगर DUMP_IT_BACK
		mb[0] = DUMP_CMD;
		mb[1] = risc_address;
		mb[4] = cnt;
		mb[3] = p_tbuf & 0xffff;
		mb[2] = (p_tbuf >> 16) & 0xffff;
		mb[7] = upper_32_bits(p_tbuf) & 0xffff;
		mb[6] = upper_32_bits(p_tbuf) >> 16;

		err = qla1280_mailbox_command(ha, CMD_ARGS, mb);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR
			       "Failed to dump partial segment of f/w\n");
			जाओ out;
		पूर्ण
		sp = (uपूर्णांक8_t *)ha->request_ring;
		क्रम (i = 0; i < (cnt << 1); i++) अणु
			अगर (tbuf[i] != sp[i] && warn++ < 10) अणु
				prपूर्णांकk(KERN_ERR "%s: FW compare error @ "
						"byte(0x%x) loop#=%x\n",
						__func__, i, num);
				prपूर्णांकk(KERN_ERR "%s: FWbyte=%x  "
						"FWfromChip=%x\n",
						__func__, sp[i], tbuf[i]);
				/*अवरोध; */
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		risc_address += cnt;
		risc_code_size = risc_code_size - cnt;
		fw_data = fw_data + cnt;
		num++;
	पूर्ण

 out:
#अगर DUMP_IT_BACK
	dma_मुक्त_coherent(&ha->pdev->dev, 8000, tbuf, p_tbuf);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल पूर्णांक
qla1280_start_firmware(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	पूर्णांक err;

	dprपूर्णांकk(1, "%s: Verifying checksum of loaded RISC code.\n",
			__func__);

	/* Verअगरy checksum of loaded RISC code. */
	mb[0] = MBC_VERIFY_CHECKSUM;
	/* mb[1] = ql12_risc_code_addr01; */
	mb[1] = ha->fwstart;
	err = qla1280_mailbox_command(ha, BIT_1 | BIT_0, mb);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "scsi(%li): RISC checksum failed.\n", ha->host_no);
		वापस err;
	पूर्ण

	/* Start firmware execution. */
	dprपूर्णांकk(1, "%s: start firmware running.\n", __func__);
	mb[0] = MBC_EXECUTE_FIRMWARE;
	mb[1] = ha->fwstart;
	err = qla1280_mailbox_command(ha, BIT_1 | BIT_0, &mb[0]);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "scsi(%li): Failed to start firmware\n",
				ha->host_no);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
qla1280_load_firmware(काष्ठा scsi_qla_host *ha)
अणु
	/* enter with host_lock taken */
	पूर्णांक err;

	err = qla1280_chip_diag(ha);
	अगर (err)
		जाओ out;
	अगर (IS_ISP1040(ha))
		err = qla1280_load_firmware_pio(ha);
	अन्यथा
		err = qla1280_load_firmware_dma(ha);
	अगर (err)
		जाओ out;
	err = qla1280_start_firmware(ha);
 out:
	वापस err;
पूर्ण

/*
 * Initialize rings
 *
 * Input:
 *      ha                = adapter block poपूर्णांकer.
 *      ha->request_ring  = request ring भव address
 *      ha->response_ring = response ring भव address
 *      ha->request_dma   = request ring physical address
 *      ha->response_dma  = response ring physical address
 *
 * Returns:
 *      0 = success.
 */
अटल पूर्णांक
qla1280_init_rings(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	पूर्णांक status = 0;

	ENTER("qla1280_init_rings");

	/* Clear outstanding commands array. */
	स_रखो(ha->outstanding_cmds, 0,
	       माप(काष्ठा srb *) * MAX_OUTSTANDING_COMMANDS);

	/* Initialize request queue. */
	ha->request_ring_ptr = ha->request_ring;
	ha->req_ring_index = 0;
	ha->req_q_cnt = REQUEST_ENTRY_CNT;
	/* mb[0] = MBC_INIT_REQUEST_QUEUE; */
	mb[0] = MBC_INIT_REQUEST_QUEUE_A64;
	mb[1] = REQUEST_ENTRY_CNT;
	mb[3] = ha->request_dma & 0xffff;
	mb[2] = (ha->request_dma >> 16) & 0xffff;
	mb[4] = 0;
	mb[7] = upper_32_bits(ha->request_dma) & 0xffff;
	mb[6] = upper_32_bits(ha->request_dma) >> 16;
	अगर (!(status = qla1280_mailbox_command(ha, BIT_7 | BIT_6 | BIT_4 |
					       BIT_3 | BIT_2 | BIT_1 | BIT_0,
					       &mb[0]))) अणु
		/* Initialize response queue. */
		ha->response_ring_ptr = ha->response_ring;
		ha->rsp_ring_index = 0;
		/* mb[0] = MBC_INIT_RESPONSE_QUEUE; */
		mb[0] = MBC_INIT_RESPONSE_QUEUE_A64;
		mb[1] = RESPONSE_ENTRY_CNT;
		mb[3] = ha->response_dma & 0xffff;
		mb[2] = (ha->response_dma >> 16) & 0xffff;
		mb[5] = 0;
		mb[7] = upper_32_bits(ha->response_dma) & 0xffff;
		mb[6] = upper_32_bits(ha->response_dma) >> 16;
		status = qla1280_mailbox_command(ha, BIT_7 | BIT_6 | BIT_5 |
						 BIT_3 | BIT_2 | BIT_1 | BIT_0,
						 &mb[0]);
	पूर्ण

	अगर (status)
		dprपूर्णांकk(2, "qla1280_init_rings: **** FAILED ****\n");

	LEAVE("qla1280_init_rings");
	वापस status;
पूर्ण

अटल व्योम
qla1280_prपूर्णांक_settings(काष्ठा nvram *nv)
अणु
	dprपूर्णांकk(1, "qla1280 : initiator scsi id bus[0]=%d\n",
		nv->bus[0].config_1.initiator_id);
	dprपूर्णांकk(1, "qla1280 : initiator scsi id bus[1]=%d\n",
		nv->bus[1].config_1.initiator_id);

	dprपूर्णांकk(1, "qla1280 : bus reset delay[0]=%d\n",
		nv->bus[0].bus_reset_delay);
	dprपूर्णांकk(1, "qla1280 : bus reset delay[1]=%d\n",
		nv->bus[1].bus_reset_delay);

	dprपूर्णांकk(1, "qla1280 : retry count[0]=%d\n", nv->bus[0].retry_count);
	dprपूर्णांकk(1, "qla1280 : retry delay[0]=%d\n", nv->bus[0].retry_delay);
	dprपूर्णांकk(1, "qla1280 : retry count[1]=%d\n", nv->bus[1].retry_count);
	dprपूर्णांकk(1, "qla1280 : retry delay[1]=%d\n", nv->bus[1].retry_delay);

	dprपूर्णांकk(1, "qla1280 : async data setup time[0]=%d\n",
		nv->bus[0].config_2.async_data_setup_समय);
	dprपूर्णांकk(1, "qla1280 : async data setup time[1]=%d\n",
		nv->bus[1].config_2.async_data_setup_समय);

	dprपूर्णांकk(1, "qla1280 : req/ack active negation[0]=%d\n",
		nv->bus[0].config_2.req_ack_active_negation);
	dprपूर्णांकk(1, "qla1280 : req/ack active negation[1]=%d\n",
		nv->bus[1].config_2.req_ack_active_negation);

	dprपूर्णांकk(1, "qla1280 : data line active negation[0]=%d\n",
		nv->bus[0].config_2.data_line_active_negation);
	dprपूर्णांकk(1, "qla1280 : data line active negation[1]=%d\n",
		nv->bus[1].config_2.data_line_active_negation);

	dprपूर्णांकk(1, "qla1280 : disable loading risc code=%d\n",
		nv->cntr_flags_1.disable_loading_risc_code);

	dprपूर्णांकk(1, "qla1280 : enable 64bit addressing=%d\n",
		nv->cntr_flags_1.enable_64bit_addressing);

	dprपूर्णांकk(1, "qla1280 : selection timeout limit[0]=%d\n",
		nv->bus[0].selection_समयout);
	dprपूर्णांकk(1, "qla1280 : selection timeout limit[1]=%d\n",
		nv->bus[1].selection_समयout);

	dprपूर्णांकk(1, "qla1280 : max queue depth[0]=%d\n",
		nv->bus[0].max_queue_depth);
	dprपूर्णांकk(1, "qla1280 : max queue depth[1]=%d\n",
		nv->bus[1].max_queue_depth);
पूर्ण

अटल व्योम
qla1280_set_target_शेषs(काष्ठा scsi_qla_host *ha, पूर्णांक bus, पूर्णांक target)
अणु
	काष्ठा nvram *nv = &ha->nvram;

	nv->bus[bus].target[target].parameter.renegotiate_on_error = 1;
	nv->bus[bus].target[target].parameter.स्वतः_request_sense = 1;
	nv->bus[bus].target[target].parameter.tag_queuing = 1;
	nv->bus[bus].target[target].parameter.enable_sync = 1;
#अगर 1	/* Some SCSI Processors करो not seem to like this */
	nv->bus[bus].target[target].parameter.enable_wide = 1;
#पूर्ण_अगर
	nv->bus[bus].target[target].execution_throttle =
		nv->bus[bus].max_queue_depth - 1;
	nv->bus[bus].target[target].parameter.parity_checking = 1;
	nv->bus[bus].target[target].parameter.disconnect_allowed = 1;

	अगर (IS_ISP1x160(ha)) अणु
		nv->bus[bus].target[target].flags.flags1x160.device_enable = 1;
		nv->bus[bus].target[target].flags.flags1x160.sync_offset = 0x0e;
		nv->bus[bus].target[target].sync_period = 9;
		nv->bus[bus].target[target].ppr_1x160.flags.enable_ppr = 1;
		nv->bus[bus].target[target].ppr_1x160.flags.ppr_options = 2;
		nv->bus[bus].target[target].ppr_1x160.flags.ppr_bus_width = 1;
	पूर्ण अन्यथा अणु
		nv->bus[bus].target[target].flags.flags1x80.device_enable = 1;
		nv->bus[bus].target[target].flags.flags1x80.sync_offset = 12;
		nv->bus[bus].target[target].sync_period = 10;
	पूर्ण
पूर्ण

अटल व्योम
qla1280_set_शेषs(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा nvram *nv = &ha->nvram;
	पूर्णांक bus, target;

	dprपूर्णांकk(1, "Using defaults for NVRAM: \n");
	स_रखो(nv, 0, माप(काष्ठा nvram));

	/* nv->cntr_flags_1.disable_loading_risc_code = 1; */
	nv->firmware_feature.f.enable_fast_posting = 1;
	nv->firmware_feature.f.disable_synchronous_backoff = 1;
	nv->termination.scsi_bus_0_control = 3;
	nv->termination.scsi_bus_1_control = 3;
	nv->termination.स्वतः_term_support = 1;

	/*
	 * Set शेष FIFO magic - What appropriate values would be here
	 * is unknown. This is what I have found testing with 12160s.
	 *
	 * Now, I would love the magic decoder ring क्रम this one, the
	 * header file provided by QLogic seems to be bogus or incomplete
	 * at best.
	 */
	nv->isp_config.burst_enable = 1;
	अगर (IS_ISP1040(ha))
		nv->isp_config.fअगरo_threshold |= 3;
	अन्यथा
		nv->isp_config.fअगरo_threshold |= 4;

	अगर (IS_ISP1x160(ha))
		nv->isp_parameter = 0x01; /* fast memory enable */

	क्रम (bus = 0; bus < MAX_BUSES; bus++) अणु
		nv->bus[bus].config_1.initiator_id = 7;
		nv->bus[bus].config_2.req_ack_active_negation = 1;
		nv->bus[bus].config_2.data_line_active_negation = 1;
		nv->bus[bus].selection_समयout = 250;
		nv->bus[bus].max_queue_depth = 32;

		अगर (IS_ISP1040(ha)) अणु
			nv->bus[bus].bus_reset_delay = 3;
			nv->bus[bus].config_2.async_data_setup_समय = 6;
			nv->bus[bus].retry_delay = 1;
		पूर्ण अन्यथा अणु
			nv->bus[bus].bus_reset_delay = 5;
			nv->bus[bus].config_2.async_data_setup_समय = 8;
		पूर्ण

		क्रम (target = 0; target < MAX_TARGETS; target++)
			qla1280_set_target_शेषs(ha, bus, target);
	पूर्ण
पूर्ण

अटल पूर्णांक
qla1280_config_target(काष्ठा scsi_qla_host *ha, पूर्णांक bus, पूर्णांक target)
अणु
	काष्ठा nvram *nv = &ha->nvram;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	पूर्णांक status, lun;
	uपूर्णांक16_t flag;

	/* Set Target Parameters. */
	mb[0] = MBC_SET_TARGET_PARAMETERS;
	mb[1] = (uपूर्णांक16_t)((bus ? target | BIT_7 : target) << 8);

	/*
	 * Do not enable sync and ppr क्रम the initial INQUIRY run. We
	 * enable this later अगर we determine the target actually
	 * supports it.
	 */
	mb[2] = (TP_RENEGOTIATE | TP_AUTO_REQUEST_SENSE | TP_TAGGED_QUEUE
		 | TP_WIDE | TP_PARITY | TP_DISCONNECT);

	अगर (IS_ISP1x160(ha))
		mb[3] =	nv->bus[bus].target[target].flags.flags1x160.sync_offset << 8;
	अन्यथा
		mb[3] =	nv->bus[bus].target[target].flags.flags1x80.sync_offset << 8;
	mb[3] |= nv->bus[bus].target[target].sync_period;
	status = qla1280_mailbox_command(ha, 0x0f, mb);

	/* Save Tag queuing enable flag. */
	flag = (BIT_0 << target);
	अगर (nv->bus[bus].target[target].parameter.tag_queuing)
		ha->bus_settings[bus].qtag_enables |= flag;

	/* Save Device enable flag. */
	अगर (IS_ISP1x160(ha)) अणु
		अगर (nv->bus[bus].target[target].flags.flags1x160.device_enable)
			ha->bus_settings[bus].device_enables |= flag;
		ha->bus_settings[bus].lun_disables |= 0;
	पूर्ण अन्यथा अणु
		अगर (nv->bus[bus].target[target].flags.flags1x80.device_enable)
			ha->bus_settings[bus].device_enables |= flag;
		/* Save LUN disable flag. */
		अगर (nv->bus[bus].target[target].flags.flags1x80.lun_disable)
			ha->bus_settings[bus].lun_disables |= flag;
	पूर्ण

	/* Set Device Queue Parameters. */
	क्रम (lun = 0; lun < MAX_LUNS; lun++) अणु
		mb[0] = MBC_SET_DEVICE_QUEUE;
		mb[1] = (uपूर्णांक16_t)((bus ? target | BIT_7 : target) << 8);
		mb[1] |= lun;
		mb[2] = nv->bus[bus].max_queue_depth;
		mb[3] = nv->bus[bus].target[target].execution_throttle;
		status |= qla1280_mailbox_command(ha, 0x0f, mb);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक
qla1280_config_bus(काष्ठा scsi_qla_host *ha, पूर्णांक bus)
अणु
	काष्ठा nvram *nv = &ha->nvram;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	पूर्णांक target, status;

	/* SCSI Reset Disable. */
	ha->bus_settings[bus].disable_scsi_reset =
		nv->bus[bus].config_1.scsi_reset_disable;

	/* Initiator ID. */
	ha->bus_settings[bus].id = nv->bus[bus].config_1.initiator_id;
	mb[0] = MBC_SET_INITIATOR_ID;
	mb[1] = bus ? ha->bus_settings[bus].id | BIT_7 :
		ha->bus_settings[bus].id;
	status = qla1280_mailbox_command(ha, BIT_1 | BIT_0, &mb[0]);

	/* Reset Delay. */
	ha->bus_settings[bus].bus_reset_delay =
		nv->bus[bus].bus_reset_delay;

	/* Command queue depth per device. */
	ha->bus_settings[bus].hiwat = nv->bus[bus].max_queue_depth - 1;

	/* Set target parameters. */
	क्रम (target = 0; target < MAX_TARGETS; target++)
		status |= qla1280_config_target(ha, bus, target);

	वापस status;
पूर्ण

अटल पूर्णांक
qla1280_nvram_config(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	काष्ठा nvram *nv = &ha->nvram;
	पूर्णांक bus, target, status = 0;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];

	ENTER("qla1280_nvram_config");

	अगर (ha->nvram_valid) अणु
		/* Always क्रमce AUTO sense क्रम LINUX SCSI */
		क्रम (bus = 0; bus < MAX_BUSES; bus++)
			क्रम (target = 0; target < MAX_TARGETS; target++) अणु
				nv->bus[bus].target[target].parameter.
					स्वतः_request_sense = 1;
			पूर्ण
	पूर्ण अन्यथा अणु
		qla1280_set_शेषs(ha);
	पूर्ण

	qla1280_prपूर्णांक_settings(nv);

	/* Disable RISC load of firmware. */
	ha->flags.disable_risc_code_load =
		nv->cntr_flags_1.disable_loading_risc_code;

	अगर (IS_ISP1040(ha)) अणु
		uपूर्णांक16_t hwrev, cfg1, cdma_conf;

		hwrev = RD_REG_WORD(&reg->cfg_0) & ISP_CFG0_HWMSK;

		cfg1 = RD_REG_WORD(&reg->cfg_1) & ~(BIT_4 | BIT_5 | BIT_6);
		cdma_conf = RD_REG_WORD(&reg->cdma_cfg);

		/* Busted fअगरo, says mjacob. */
		अगर (hwrev != ISP_CFG0_1040A)
			cfg1 |= nv->isp_config.fअगरo_threshold << 4;

		cfg1 |= nv->isp_config.burst_enable << 2;
		WRT_REG_WORD(&reg->cfg_1, cfg1);

		WRT_REG_WORD(&reg->cdma_cfg, cdma_conf | CDMA_CONF_BENAB);
		WRT_REG_WORD(&reg->ddma_cfg, cdma_conf | DDMA_CONF_BENAB);
	पूर्ण अन्यथा अणु
		uपूर्णांक16_t cfg1, term;

		/* Set ISP hardware DMA burst */
		cfg1 = nv->isp_config.fअगरo_threshold << 4;
		cfg1 |= nv->isp_config.burst_enable << 2;
		/* Enable DMA arbitration on dual channel controllers */
		अगर (ha->ports > 1)
			cfg1 |= BIT_13;
		WRT_REG_WORD(&reg->cfg_1, cfg1);

		/* Set SCSI termination. */
		WRT_REG_WORD(&reg->gpio_enable,
			     BIT_7 | BIT_3 | BIT_2 | BIT_1 | BIT_0);
		term = nv->termination.scsi_bus_1_control;
		term |= nv->termination.scsi_bus_0_control << 2;
		term |= nv->termination.स्वतः_term_support << 7;
		RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
		WRT_REG_WORD(&reg->gpio_data, term);
	पूर्ण
	RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */

	/* ISP parameter word. */
	mb[0] = MBC_SET_SYSTEM_PARAMETER;
	mb[1] = nv->isp_parameter;
	status |= qla1280_mailbox_command(ha, BIT_1 | BIT_0, &mb[0]);

	अगर (IS_ISP1x40(ha)) अणु
		/* घड़ी rate - क्रम qla1240 and older, only */
		mb[0] = MBC_SET_CLOCK_RATE;
		mb[1] = 40;
	 	status |= qla1280_mailbox_command(ha, BIT_1 | BIT_0, mb);
	पूर्ण

	/* Firmware feature word. */
	mb[0] = MBC_SET_FIRMWARE_FEATURES;
	mb[1] = nv->firmware_feature.f.enable_fast_posting;
	mb[1] |= nv->firmware_feature.f.report_lvd_bus_transition << 1;
	mb[1] |= nv->firmware_feature.f.disable_synchronous_backoff << 5;
	status |= qla1280_mailbox_command(ha, BIT_1 | BIT_0, mb);

	/* Retry count and delay. */
	mb[0] = MBC_SET_RETRY_COUNT;
	mb[1] = nv->bus[0].retry_count;
	mb[2] = nv->bus[0].retry_delay;
	mb[6] = nv->bus[1].retry_count;
	mb[7] = nv->bus[1].retry_delay;
	status |= qla1280_mailbox_command(ha, BIT_7 | BIT_6 | BIT_2 |
					  BIT_1 | BIT_0, &mb[0]);

	/* ASYNC data setup समय. */
	mb[0] = MBC_SET_ASYNC_DATA_SETUP;
	mb[1] = nv->bus[0].config_2.async_data_setup_समय;
	mb[2] = nv->bus[1].config_2.async_data_setup_समय;
	status |= qla1280_mailbox_command(ha, BIT_2 | BIT_1 | BIT_0, &mb[0]);

	/* Active negation states. */
	mb[0] = MBC_SET_ACTIVE_NEGATION;
	mb[1] = 0;
	अगर (nv->bus[0].config_2.req_ack_active_negation)
		mb[1] |= BIT_5;
	अगर (nv->bus[0].config_2.data_line_active_negation)
		mb[1] |= BIT_4;
	mb[2] = 0;
	अगर (nv->bus[1].config_2.req_ack_active_negation)
		mb[2] |= BIT_5;
	अगर (nv->bus[1].config_2.data_line_active_negation)
		mb[2] |= BIT_4;
	status |= qla1280_mailbox_command(ha, BIT_2 | BIT_1 | BIT_0, mb);

	mb[0] = MBC_SET_DATA_OVERRUN_RECOVERY;
	mb[1] = 2;	/* Reset SCSI bus and वापस all outstanding IO */
	status |= qla1280_mailbox_command(ha, BIT_1 | BIT_0, mb);

	/* thingy */
	mb[0] = MBC_SET_PCI_CONTROL;
	mb[1] = BIT_1;	/* Data DMA Channel Burst Enable */
	mb[2] = BIT_1;	/* Command DMA Channel Burst Enable */
	status |= qla1280_mailbox_command(ha, BIT_2 | BIT_1 | BIT_0, mb);

	mb[0] = MBC_SET_TAG_AGE_LIMIT;
	mb[1] = 8;
	status |= qla1280_mailbox_command(ha, BIT_1 | BIT_0, mb);

	/* Selection समयout. */
	mb[0] = MBC_SET_SELECTION_TIMEOUT;
	mb[1] = nv->bus[0].selection_समयout;
	mb[2] = nv->bus[1].selection_समयout;
	status |= qla1280_mailbox_command(ha, BIT_2 | BIT_1 | BIT_0, mb);

	क्रम (bus = 0; bus < ha->ports; bus++)
		status |= qla1280_config_bus(ha, bus);

	अगर (status)
		dprपूर्णांकk(2, "qla1280_nvram_config: **** FAILED ****\n");

	LEAVE("qla1280_nvram_config");
	वापस status;
पूर्ण

/*
 * Get NVRAM data word
 *      Calculates word position in NVRAM and calls request routine to
 *      get the word from NVRAM.
 *
 * Input:
 *      ha      = adapter block poपूर्णांकer.
 *      address = NVRAM word address.
 *
 * Returns:
 *      data word.
 */
अटल uपूर्णांक16_t
qla1280_get_nvram_word(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t address)
अणु
	uपूर्णांक32_t nv_cmd;
	uपूर्णांक16_t data;

	nv_cmd = address << 16;
	nv_cmd |= NV_READ_OP;

	data = le16_to_cpu(qla1280_nvram_request(ha, nv_cmd));

	dprपूर्णांकk(8, "qla1280_get_nvram_word: exiting normally NVRAM data = "
		"0x%x", data);

	वापस data;
पूर्ण

/*
 * NVRAM request
 *      Sends पढ़ो command to NVRAM and माला_लो data from NVRAM.
 *
 * Input:
 *      ha     = adapter block poपूर्णांकer.
 *      nv_cmd = Bit 26     = start bit
 *               Bit 25, 24 = opcode
 *               Bit 23-16  = address
 *               Bit 15-0   = ग_लिखो data
 *
 * Returns:
 *      data word.
 */
अटल uपूर्णांक16_t
qla1280_nvram_request(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t nv_cmd)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	पूर्णांक cnt;
	uपूर्णांक16_t data = 0;
	uपूर्णांक16_t reg_data;

	/* Send command to NVRAM. */

	nv_cmd <<= 5;
	क्रम (cnt = 0; cnt < 11; cnt++) अणु
		अगर (nv_cmd & BIT_31)
			qla1280_nv_ग_लिखो(ha, NV_DATA_OUT);
		अन्यथा
			qla1280_nv_ग_लिखो(ha, 0);
		nv_cmd <<= 1;
	पूर्ण

	/* Read data from NVRAM. */

	क्रम (cnt = 0; cnt < 16; cnt++) अणु
		WRT_REG_WORD(&reg->nvram, (NV_SELECT | NV_CLOCK));
		RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
		NVRAM_DELAY();
		data <<= 1;
		reg_data = RD_REG_WORD(&reg->nvram);
		अगर (reg_data & NV_DATA_IN)
			data |= BIT_0;
		WRT_REG_WORD(&reg->nvram, NV_SELECT);
		RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
		NVRAM_DELAY();
	पूर्ण

	/* Deselect chip. */

	WRT_REG_WORD(&reg->nvram, NV_DESELECT);
	RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
	NVRAM_DELAY();

	वापस data;
पूर्ण

अटल व्योम
qla1280_nv_ग_लिखो(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t data)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;

	WRT_REG_WORD(&reg->nvram, data | NV_SELECT);
	RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
	NVRAM_DELAY();
	WRT_REG_WORD(&reg->nvram, data | NV_SELECT | NV_CLOCK);
	RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
	NVRAM_DELAY();
	WRT_REG_WORD(&reg->nvram, data | NV_SELECT);
	RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */
	NVRAM_DELAY();
पूर्ण

/*
 * Mailbox Command
 *      Issue mailbox command and रुकोs क्रम completion.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *      mr = mailbox रेजिस्टरs to load.
 *      mb = data poपूर्णांकer क्रम mailbox रेजिस्टरs.
 *
 * Output:
 *      mb[MAILBOX_REGISTER_COUNT] = वापसed mailbox data.
 *
 * Returns:
 *      0 = success
 */
अटल पूर्णांक
qla1280_mailbox_command(काष्ठा scsi_qla_host *ha, uपूर्णांक8_t mr, uपूर्णांक16_t *mb)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	पूर्णांक status = 0;
	पूर्णांक cnt;
	uपूर्णांक16_t *optr, *iptr;
	uपूर्णांक16_t __iomem *mptr;
	DECLARE_COMPLETION_ONSTACK(रुको);

	ENTER("qla1280_mailbox_command");

	अगर (ha->mailbox_रुको) अणु
		prपूर्णांकk(KERN_ERR "Warning mailbox wait already in use!\n");
	पूर्ण
	ha->mailbox_रुको = &रुको;

	/*
	 * We really should start out by verअगरying that the mailbox is
	 * available beक्रमe starting sending the command data
	 */
	/* Load mailbox रेजिस्टरs. */
	mptr = (uपूर्णांक16_t __iomem *) &reg->mailbox0;
	iptr = mb;
	क्रम (cnt = 0; cnt < MAILBOX_REGISTER_COUNT; cnt++) अणु
		अगर (mr & BIT_0) अणु
			WRT_REG_WORD(mptr, (*iptr));
		पूर्ण

		mr >>= 1;
		mptr++;
		iptr++;
	पूर्ण

	/* Issue set host पूर्णांकerrupt command. */

	/* set up a समयr just in हाल we're really jammed */
	समयr_setup(&ha->mailbox_समयr, qla1280_mailbox_समयout, 0);
	mod_समयr(&ha->mailbox_समयr, jअगरfies + 20 * HZ);

	spin_unlock_irq(ha->host->host_lock);
	WRT_REG_WORD(&reg->host_cmd, HC_SET_HOST_INT);
	qla1280_debounce_रेजिस्टर(&reg->istatus);

	रुको_क्रम_completion(&रुको);
	del_समयr_sync(&ha->mailbox_समयr);

	spin_lock_irq(ha->host->host_lock);

	ha->mailbox_रुको = शून्य;

	/* Check क्रम mailbox command समयout. */
	अगर (ha->mailbox_out[0] != MBS_CMD_CMP) अणु
		prपूर्णांकk(KERN_WARNING "qla1280_mailbox_command: Command failed, "
		       "mailbox0 = 0x%04x, mailbox_out0 = 0x%04x, istatus = "
		       "0x%04x\n", 
		       mb[0], ha->mailbox_out[0], RD_REG_WORD(&reg->istatus));
		prपूर्णांकk(KERN_WARNING "m0 %04x, m1 %04x, m2 %04x, m3 %04x\n",
		       RD_REG_WORD(&reg->mailbox0), RD_REG_WORD(&reg->mailbox1),
		       RD_REG_WORD(&reg->mailbox2), RD_REG_WORD(&reg->mailbox3));
		prपूर्णांकk(KERN_WARNING "m4 %04x, m5 %04x, m6 %04x, m7 %04x\n",
		       RD_REG_WORD(&reg->mailbox4), RD_REG_WORD(&reg->mailbox5),
		       RD_REG_WORD(&reg->mailbox6), RD_REG_WORD(&reg->mailbox7));
		status = 1;
	पूर्ण

	/* Load वापस mailbox रेजिस्टरs. */
	optr = mb;
	iptr = (uपूर्णांक16_t *) &ha->mailbox_out[0];
	mr = MAILBOX_REGISTER_COUNT;
	स_नकल(optr, iptr, MAILBOX_REGISTER_COUNT * माप(uपूर्णांक16_t));

	अगर (ha->flags.reset_marker)
		qla1280_rst_aen(ha);

	अगर (status)
		dprपूर्णांकk(2, "qla1280_mailbox_command: **** FAILED, mailbox0 = "
			"0x%x ****\n", mb[0]);

	LEAVE("qla1280_mailbox_command");
	वापस status;
पूर्ण

/*
 * qla1280_poll
 *      Polls ISP क्रम पूर्णांकerrupts.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 */
अटल व्योम
qla1280_poll(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	uपूर्णांक16_t data;
	LIST_HEAD(करोne_q);

	/* ENTER("qla1280_poll"); */

	/* Check क्रम pending पूर्णांकerrupts. */
	data = RD_REG_WORD(&reg->istatus);
	अगर (data & RISC_INT)
		qla1280_isr(ha, &करोne_q);

	अगर (!ha->mailbox_रुको) अणु
		अगर (ha->flags.reset_marker)
			qla1280_rst_aen(ha);
	पूर्ण

	अगर (!list_empty(&करोne_q))
		qla1280_करोne(ha);

	/* LEAVE("qla1280_poll"); */
पूर्ण

/*
 * qla1280_bus_reset
 *      Issue SCSI bus reset.
 *
 * Input:
 *      ha  = adapter block poपूर्णांकer.
 *      bus = SCSI bus number.
 *
 * Returns:
 *      0 = success
 */
अटल पूर्णांक
qla1280_bus_reset(काष्ठा scsi_qla_host *ha, पूर्णांक bus)
अणु
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	uपूर्णांक16_t reset_delay;
	पूर्णांक status;

	dprपूर्णांकk(3, "qla1280_bus_reset: entered\n");

	अगर (qla1280_verbose)
		prपूर्णांकk(KERN_INFO "scsi(%li:%i): Resetting SCSI BUS\n",
		       ha->host_no, bus);

	reset_delay = ha->bus_settings[bus].bus_reset_delay;
	mb[0] = MBC_BUS_RESET;
	mb[1] = reset_delay;
	mb[2] = (uपूर्णांक16_t) bus;
	status = qla1280_mailbox_command(ha, BIT_2 | BIT_1 | BIT_0, &mb[0]);

	अगर (status) अणु
		अगर (ha->bus_settings[bus].failed_reset_count > 2)
			ha->bus_settings[bus].scsi_bus_dead = 1;
		ha->bus_settings[bus].failed_reset_count++;
	पूर्ण अन्यथा अणु
		spin_unlock_irq(ha->host->host_lock);
		ssleep(reset_delay);
		spin_lock_irq(ha->host->host_lock);

		ha->bus_settings[bus].scsi_bus_dead = 0;
		ha->bus_settings[bus].failed_reset_count = 0;
		ha->bus_settings[bus].reset_marker = 0;
		/* Issue marker command. */
		qla1280_marker(ha, bus, 0, 0, MK_SYNC_ALL);
	पूर्ण

	/*
	 * We should probably call qla1280_set_target_parameters()
	 * here as well क्रम all devices on the bus.
	 */

	अगर (status)
		dprपूर्णांकk(2, "qla1280_bus_reset: **** FAILED ****\n");
	अन्यथा
		dprपूर्णांकk(3, "qla1280_bus_reset: exiting normally\n");

	वापस status;
पूर्ण

/*
 * qla1280_device_reset
 *      Issue bus device reset message to the target.
 *
 * Input:
 *      ha      = adapter block poपूर्णांकer.
 *      bus     = SCSI BUS number.
 *      target  = SCSI ID.
 *
 * Returns:
 *      0 = success
 */
अटल पूर्णांक
qla1280_device_reset(काष्ठा scsi_qla_host *ha, पूर्णांक bus, पूर्णांक target)
अणु
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	पूर्णांक status;

	ENTER("qla1280_device_reset");

	mb[0] = MBC_ABORT_TARGET;
	mb[1] = (bus ? (target | BIT_7) : target) << 8;
	mb[2] = 1;
	status = qla1280_mailbox_command(ha, BIT_2 | BIT_1 | BIT_0, &mb[0]);

	/* Issue marker command. */
	qla1280_marker(ha, bus, target, 0, MK_SYNC_ID);

	अगर (status)
		dprपूर्णांकk(2, "qla1280_device_reset: **** FAILED ****\n");

	LEAVE("qla1280_device_reset");
	वापस status;
पूर्ण

/*
 * qla1280_पात_command
 *      Abort command पातs a specअगरied IOCB.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *      sp = SB काष्ठाure poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
अटल पूर्णांक
qla1280_पात_command(काष्ठा scsi_qla_host *ha, काष्ठा srb * sp, पूर्णांक handle)
अणु
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	अचिन्हित पूर्णांक bus, target, lun;
	पूर्णांक status;

	ENTER("qla1280_abort_command");

	bus = SCSI_BUS_32(sp->cmd);
	target = SCSI_TCN_32(sp->cmd);
	lun = SCSI_LUN_32(sp->cmd);

	sp->flags |= SRB_ABORT_PENDING;

	mb[0] = MBC_ABORT_COMMAND;
	mb[1] = (bus ? target | BIT_7 : target) << 8 | lun;
	mb[2] = handle >> 16;
	mb[3] = handle & 0xffff;
	status = qla1280_mailbox_command(ha, 0x0f, &mb[0]);

	अगर (status) अणु
		dprपूर्णांकk(2, "qla1280_abort_command: **** FAILED ****\n");
		sp->flags &= ~SRB_ABORT_PENDING;
	पूर्ण


	LEAVE("qla1280_abort_command");
	वापस status;
पूर्ण

/*
 * qla1280_reset_adapter
 *      Reset adapter.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 */
अटल व्योम
qla1280_reset_adapter(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;

	ENTER("qla1280_reset_adapter");

	/* Disable ISP chip */
	ha->flags.online = 0;
	WRT_REG_WORD(&reg->ictrl, ISP_RESET);
	WRT_REG_WORD(&reg->host_cmd,
		     HC_RESET_RISC | HC_RELEASE_RISC | HC_DISABLE_BIOS);
	RD_REG_WORD(&reg->id_l);	/* Flush PCI ग_लिखो */

	LEAVE("qla1280_reset_adapter");
पूर्ण

/*
 *  Issue marker command.
 *      Function issues marker IOCB.
 *
 * Input:
 *      ha   = adapter block poपूर्णांकer.
 *      bus  = SCSI BUS number
 *      id   = SCSI ID
 *      lun  = SCSI LUN
 *      type = marker modअगरier
 */
अटल व्योम
qla1280_marker(काष्ठा scsi_qla_host *ha, पूर्णांक bus, पूर्णांक id, पूर्णांक lun, u8 type)
अणु
	काष्ठा mrk_entry *pkt;

	ENTER("qla1280_marker");

	/* Get request packet. */
	अगर ((pkt = (काष्ठा mrk_entry *) qla1280_req_pkt(ha))) अणु
		pkt->entry_type = MARKER_TYPE;
		pkt->lun = (uपूर्णांक8_t) lun;
		pkt->target = (uपूर्णांक8_t) (bus ? (id | BIT_7) : id);
		pkt->modअगरier = type;
		pkt->entry_status = 0;

		/* Issue command to ISP */
		qla1280_isp_cmd(ha);
	पूर्ण

	LEAVE("qla1280_marker");
पूर्ण


/*
 * qla1280_64bit_start_scsi
 *      The start SCSI is responsible क्रम building request packets on
 *      request ring and modअगरying ISP input poपूर्णांकer.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *      sp = SB काष्ठाure poपूर्णांकer.
 *
 * Returns:
 *      0 = success, was able to issue command.
 */
#अगर_घोषित QLA_64BIT_PTR
अटल पूर्णांक
qla1280_64bit_start_scsi(काष्ठा scsi_qla_host *ha, काष्ठा srb * sp)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	काष्ठा scsi_cmnd *cmd = sp->cmd;
	cmd_a64_entry_t *pkt;
	__le32 *dword_ptr;
	dma_addr_t dma_handle;
	पूर्णांक status = 0;
	पूर्णांक cnt;
	पूर्णांक req_cnt;
	पूर्णांक seg_cnt;
	u8 dir;

	ENTER("qla1280_64bit_start_scsi:");

	/* Calculate number of entries and segments required. */
	req_cnt = 1;
	seg_cnt = scsi_dma_map(cmd);
	अगर (seg_cnt > 0) अणु
		अगर (seg_cnt > 2) अणु
			req_cnt += (seg_cnt - 2) / 5;
			अगर ((seg_cnt - 2) % 5)
				req_cnt++;
		पूर्ण
	पूर्ण अन्यथा अगर (seg_cnt < 0) अणु
		status = 1;
		जाओ out;
	पूर्ण

	अगर ((req_cnt + 2) >= ha->req_q_cnt) अणु
		/* Calculate number of मुक्त request entries. */
		cnt = RD_REG_WORD(&reg->mailbox4);
		अगर (ha->req_ring_index < cnt)
			ha->req_q_cnt = cnt - ha->req_ring_index;
		अन्यथा
			ha->req_q_cnt =
				REQUEST_ENTRY_CNT - (ha->req_ring_index - cnt);
	पूर्ण

	dprपूर्णांकk(3, "Number of free entries=(%d) seg_cnt=0x%x\n",
		ha->req_q_cnt, seg_cnt);

	/* If room क्रम request in request ring. */
	अगर ((req_cnt + 2) >= ha->req_q_cnt) अणु
		status = SCSI_MLQUEUE_HOST_BUSY;
		dprपूर्णांकk(2, "qla1280_start_scsi: in-ptr=0x%x  req_q_cnt="
			"0x%xreq_cnt=0x%x", ha->req_ring_index, ha->req_q_cnt,
			req_cnt);
		जाओ out;
	पूर्ण

	/* Check क्रम room in outstanding command list. */
	क्रम (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS &&
		     ha->outstanding_cmds[cnt] != शून्य; cnt++);

	अगर (cnt >= MAX_OUTSTANDING_COMMANDS) अणु
		status = SCSI_MLQUEUE_HOST_BUSY;
		dprपूर्णांकk(2, "qla1280_start_scsi: NO ROOM IN "
			"OUTSTANDING ARRAY, req_q_cnt=0x%x", ha->req_q_cnt);
		जाओ out;
	पूर्ण

	ha->outstanding_cmds[cnt] = sp;
	ha->req_q_cnt -= req_cnt;
	CMD_HANDLE(sp->cmd) = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)(cnt + 1);

	dprपूर्णांकk(2, "start: cmd=%p sp=%p CDB=%xm, handle %lx\n", cmd, sp,
		cmd->cmnd[0], (दीर्घ)CMD_HANDLE(sp->cmd));
	dprपूर्णांकk(2, "             bus %i, target %i, lun %i\n",
		SCSI_BUS_32(cmd), SCSI_TCN_32(cmd), SCSI_LUN_32(cmd));
	qla1280_dump_buffer(2, cmd->cmnd, MAX_COMMAND_SIZE);

	/*
	 * Build command packet.
	 */
	pkt = (cmd_a64_entry_t *) ha->request_ring_ptr;

	pkt->entry_type = COMMAND_A64_TYPE;
	pkt->entry_count = (uपूर्णांक8_t) req_cnt;
	pkt->sys_define = (uपूर्णांक8_t) ha->req_ring_index;
	pkt->entry_status = 0;
	pkt->handle = cpu_to_le32(cnt);

	/* Zero out reमुख्यing portion of packet. */
	स_रखो(((अक्षर *)pkt + 8), 0, (REQUEST_ENTRY_SIZE - 8));

	/* Set ISP command समयout. */
	pkt->समयout = cpu_to_le16(cmd->request->समयout/HZ);

	/* Set device target ID and LUN */
	pkt->lun = SCSI_LUN_32(cmd);
	pkt->target = SCSI_BUS_32(cmd) ?
		(SCSI_TCN_32(cmd) | BIT_7) : SCSI_TCN_32(cmd);

	/* Enable simple tag queuing अगर device supports it. */
	अगर (cmd->device->simple_tags)
		pkt->control_flags |= cpu_to_le16(BIT_3);

	/* Load SCSI command packet. */
	pkt->cdb_len = cpu_to_le16(CMD_CDBLEN(cmd));
	स_नकल(pkt->scsi_cdb, CMD_CDBP(cmd), CMD_CDBLEN(cmd));
	/* dprपूर्णांकk(1, "Build packet for command[0]=0x%x\n",pkt->scsi_cdb[0]); */

	/* Set transfer direction. */
	dir = qla1280_data_direction(cmd);
	pkt->control_flags |= cpu_to_le16(dir);

	/* Set total data segment count. */
	pkt->dseg_count = cpu_to_le16(seg_cnt);

	/*
	 * Load data segments.
	 */
	अगर (seg_cnt) अणु	/* If data transfer. */
		काष्ठा scatterlist *sg, *s;
		पूर्णांक remseg = seg_cnt;

		sg = scsi_sglist(cmd);

		/* Setup packet address segment poपूर्णांकer. */
		dword_ptr = (u32 *)&pkt->dseg_0_address;

		/* Load command entry data segments. */
		क्रम_each_sg(sg, s, seg_cnt, cnt) अणु
			अगर (cnt == 2)
				अवरोध;

			dma_handle = sg_dma_address(s);
			*dword_ptr++ =
				cpu_to_le32(lower_32_bits(dma_handle));
			*dword_ptr++ =
				cpu_to_le32(upper_32_bits(dma_handle));
			*dword_ptr++ = cpu_to_le32(sg_dma_len(s));
			dprपूर्णांकk(3, "S/G Segment phys_addr=%x %x, len=0x%x\n",
				cpu_to_le32(upper_32_bits(dma_handle)),
				cpu_to_le32(lower_32_bits(dma_handle)),
				cpu_to_le32(sg_dma_len(sg_next(s))));
			remseg--;
		पूर्ण
		dprपूर्णांकk(5, "qla1280_64bit_start_scsi: Scatter/gather "
			"command packet data - b %i, t %i, l %i \n",
			SCSI_BUS_32(cmd), SCSI_TCN_32(cmd),
			SCSI_LUN_32(cmd));
		qla1280_dump_buffer(5, (अक्षर *)pkt,
				    REQUEST_ENTRY_SIZE);

		/*
		 * Build continuation packets.
		 */
		dprपूर्णांकk(3, "S/G Building Continuation...seg_cnt=0x%x "
			"remains\n", seg_cnt);

		जबतक (remseg > 0) अणु
			/* Update sg start */
			sg = s;
			/* Adjust ring index. */
			ha->req_ring_index++;
			अगर (ha->req_ring_index == REQUEST_ENTRY_CNT) अणु
				ha->req_ring_index = 0;
				ha->request_ring_ptr =
					ha->request_ring;
			पूर्ण अन्यथा
				ha->request_ring_ptr++;

			pkt = (cmd_a64_entry_t *)ha->request_ring_ptr;

			/* Zero out packet. */
			स_रखो(pkt, 0, REQUEST_ENTRY_SIZE);

			/* Load packet शेषs. */
			((काष्ठा cont_a64_entry *) pkt)->entry_type =
				CONTINUE_A64_TYPE;
			((काष्ठा cont_a64_entry *) pkt)->entry_count = 1;
			((काष्ठा cont_a64_entry *) pkt)->sys_define =
				(uपूर्णांक8_t)ha->req_ring_index;
			/* Setup packet address segment poपूर्णांकer. */
			dword_ptr =
				(u32 *)&((काष्ठा cont_a64_entry *) pkt)->dseg_0_address;

			/* Load continuation entry data segments. */
			क्रम_each_sg(sg, s, remseg, cnt) अणु
				अगर (cnt == 5)
					अवरोध;
				dma_handle = sg_dma_address(s);
				*dword_ptr++ =
					cpu_to_le32(lower_32_bits(dma_handle));
				*dword_ptr++ =
					cpu_to_le32(upper_32_bits(dma_handle));
				*dword_ptr++ =
					cpu_to_le32(sg_dma_len(s));
				dprपूर्णांकk(3, "S/G Segment Cont. phys_addr=%x %x, len=0x%x\n",
					cpu_to_le32(upper_32_bits(dma_handle)),
					cpu_to_le32(lower_32_bits(dma_handle)),
					cpu_to_le32(sg_dma_len(s)));
			पूर्ण
			remseg -= cnt;
			dprपूर्णांकk(5, "qla1280_64bit_start_scsi: "
				"continuation packet data - b %i, t "
				"%i, l %i \n", SCSI_BUS_32(cmd),
				SCSI_TCN_32(cmd), SCSI_LUN_32(cmd));
			qla1280_dump_buffer(5, (अक्षर *)pkt,
					    REQUEST_ENTRY_SIZE);
		पूर्ण
	पूर्ण अन्यथा अणु	/* No data transfer */
		dprपूर्णांकk(5, "qla1280_64bit_start_scsi: No data, command "
			"packet data - b %i, t %i, l %i \n",
			SCSI_BUS_32(cmd), SCSI_TCN_32(cmd), SCSI_LUN_32(cmd));
		qla1280_dump_buffer(5, (अक्षर *)pkt, REQUEST_ENTRY_SIZE);
	पूर्ण
	/* Adjust ring index. */
	ha->req_ring_index++;
	अगर (ha->req_ring_index == REQUEST_ENTRY_CNT) अणु
		ha->req_ring_index = 0;
		ha->request_ring_ptr = ha->request_ring;
	पूर्ण अन्यथा
		ha->request_ring_ptr++;

	/* Set chip new ring index. */
	dprपूर्णांकk(2,
		"qla1280_64bit_start_scsi: Wakeup RISC for pending command\n");
	sp->flags |= SRB_SENT;
	ha->actthपढ़ोs++;
	WRT_REG_WORD(&reg->mailbox4, ha->req_ring_index);

 out:
	अगर (status)
		dprपूर्णांकk(2, "qla1280_64bit_start_scsi: **** FAILED ****\n");
	अन्यथा
		dprपूर्णांकk(3, "qla1280_64bit_start_scsi: exiting normally\n");

	वापस status;
पूर्ण
#अन्यथा /* !QLA_64BIT_PTR */

/*
 * qla1280_32bit_start_scsi
 *      The start SCSI is responsible क्रम building request packets on
 *      request ring and modअगरying ISP input poपूर्णांकer.
 *
 *      The Qlogic firmware पूर्णांकerface allows every queue slot to have a SCSI
 *      command and up to 4 scatter/gather (SG) entries.  If we need more
 *      than 4 SG entries, then continuation entries are used that can
 *      hold another 7 entries each.  The start routine determines अगर there
 *      is eought empty slots then build the combination of requests to
 *      fulfill the OS request.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *      sp = SCSI Request Block काष्ठाure poपूर्णांकer.
 *
 * Returns:
 *      0 = success, was able to issue command.
 */
अटल पूर्णांक
qla1280_32bit_start_scsi(काष्ठा scsi_qla_host *ha, काष्ठा srb * sp)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	काष्ठा scsi_cmnd *cmd = sp->cmd;
	काष्ठा cmd_entry *pkt;
	__le32 *dword_ptr;
	पूर्णांक status = 0;
	पूर्णांक cnt;
	पूर्णांक req_cnt;
	पूर्णांक seg_cnt;
	u8 dir;

	ENTER("qla1280_32bit_start_scsi");

	dprपूर्णांकk(1, "32bit_start: cmd=%p sp=%p CDB=%x\n", cmd, sp,
		cmd->cmnd[0]);

	/* Calculate number of entries and segments required. */
	req_cnt = 1;
	seg_cnt = scsi_dma_map(cmd);
	अगर (seg_cnt) अणु
		/*
		 * अगर greater than four sg entries then we need to allocate
		 * continuation entries
		 */
		अगर (seg_cnt > 4) अणु
			req_cnt += (seg_cnt - 4) / 7;
			अगर ((seg_cnt - 4) % 7)
				req_cnt++;
		पूर्ण
		dprपूर्णांकk(3, "S/G Transfer cmd=%p seg_cnt=0x%x, req_cnt=%x\n",
			cmd, seg_cnt, req_cnt);
	पूर्ण अन्यथा अगर (seg_cnt < 0) अणु
		status = 1;
		जाओ out;
	पूर्ण

	अगर ((req_cnt + 2) >= ha->req_q_cnt) अणु
		/* Calculate number of मुक्त request entries. */
		cnt = RD_REG_WORD(&reg->mailbox4);
		अगर (ha->req_ring_index < cnt)
			ha->req_q_cnt = cnt - ha->req_ring_index;
		अन्यथा
			ha->req_q_cnt =
				REQUEST_ENTRY_CNT - (ha->req_ring_index - cnt);
	पूर्ण

	dprपूर्णांकk(3, "Number of free entries=(%d) seg_cnt=0x%x\n",
		ha->req_q_cnt, seg_cnt);
	/* If room क्रम request in request ring. */
	अगर ((req_cnt + 2) >= ha->req_q_cnt) अणु
		status = SCSI_MLQUEUE_HOST_BUSY;
		dprपूर्णांकk(2, "qla1280_32bit_start_scsi: in-ptr=0x%x, "
			"req_q_cnt=0x%x, req_cnt=0x%x", ha->req_ring_index,
			ha->req_q_cnt, req_cnt);
		जाओ out;
	पूर्ण

	/* Check क्रम empty slot in outstanding command list. */
	क्रम (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS &&
	     ha->outstanding_cmds[cnt]; cnt++);

	अगर (cnt >= MAX_OUTSTANDING_COMMANDS) अणु
		status = SCSI_MLQUEUE_HOST_BUSY;
		dprपूर्णांकk(2, "qla1280_32bit_start_scsi: NO ROOM IN OUTSTANDING "
			"ARRAY, req_q_cnt=0x%x\n", ha->req_q_cnt);
		जाओ out;
	पूर्ण

	CMD_HANDLE(sp->cmd) = (अचिन्हित अक्षर *) (अचिन्हित दीर्घ)(cnt + 1);
	ha->outstanding_cmds[cnt] = sp;
	ha->req_q_cnt -= req_cnt;

	/*
	 * Build command packet.
	 */
	pkt = (काष्ठा cmd_entry *) ha->request_ring_ptr;

	pkt->entry_type = COMMAND_TYPE;
	pkt->entry_count = (uपूर्णांक8_t) req_cnt;
	pkt->sys_define = (uपूर्णांक8_t) ha->req_ring_index;
	pkt->entry_status = 0;
	pkt->handle = cpu_to_le32(cnt);

	/* Zero out reमुख्यing portion of packet. */
	स_रखो(((अक्षर *)pkt + 8), 0, (REQUEST_ENTRY_SIZE - 8));

	/* Set ISP command समयout. */
	pkt->समयout = cpu_to_le16(cmd->request->समयout/HZ);

	/* Set device target ID and LUN */
	pkt->lun = SCSI_LUN_32(cmd);
	pkt->target = SCSI_BUS_32(cmd) ?
		(SCSI_TCN_32(cmd) | BIT_7) : SCSI_TCN_32(cmd);

	/* Enable simple tag queuing अगर device supports it. */
	अगर (cmd->device->simple_tags)
		pkt->control_flags |= cpu_to_le16(BIT_3);

	/* Load SCSI command packet. */
	pkt->cdb_len = cpu_to_le16(CMD_CDBLEN(cmd));
	स_नकल(pkt->scsi_cdb, CMD_CDBP(cmd), CMD_CDBLEN(cmd));

	/*dprपूर्णांकk(1, "Build packet for command[0]=0x%x\n",pkt->scsi_cdb[0]); */
	/* Set transfer direction. */
	dir = qla1280_data_direction(cmd);
	pkt->control_flags |= cpu_to_le16(dir);

	/* Set total data segment count. */
	pkt->dseg_count = cpu_to_le16(seg_cnt);

	/*
	 * Load data segments.
	 */
	अगर (seg_cnt) अणु
		काष्ठा scatterlist *sg, *s;
		पूर्णांक remseg = seg_cnt;

		sg = scsi_sglist(cmd);

		/* Setup packet address segment poपूर्णांकer. */
		dword_ptr = &pkt->dseg_0_address;

		dprपूर्णांकk(3, "Building S/G data segments..\n");
		qla1280_dump_buffer(1, (अक्षर *)sg, 4 * 16);

		/* Load command entry data segments. */
		क्रम_each_sg(sg, s, seg_cnt, cnt) अणु
			अगर (cnt == 4)
				अवरोध;
			*dword_ptr++ =
				cpu_to_le32(lower_32_bits(sg_dma_address(s)));
			*dword_ptr++ = cpu_to_le32(sg_dma_len(s));
			dprपूर्णांकk(3, "S/G Segment phys_addr=0x%lx, len=0x%x\n",
				(lower_32_bits(sg_dma_address(s))),
				(sg_dma_len(s)));
			remseg--;
		पूर्ण
		/*
		 * Build continuation packets.
		 */
		dprपूर्णांकk(3, "S/G Building Continuation"
			"...seg_cnt=0x%x remains\n", seg_cnt);
		जबतक (remseg > 0) अणु
			/* Continue from end poपूर्णांक */
			sg = s;
			/* Adjust ring index. */
			ha->req_ring_index++;
			अगर (ha->req_ring_index == REQUEST_ENTRY_CNT) अणु
				ha->req_ring_index = 0;
				ha->request_ring_ptr =
					ha->request_ring;
			पूर्ण अन्यथा
				ha->request_ring_ptr++;

			pkt = (काष्ठा cmd_entry *)ha->request_ring_ptr;

			/* Zero out packet. */
			स_रखो(pkt, 0, REQUEST_ENTRY_SIZE);

			/* Load packet शेषs. */
			((काष्ठा cont_entry *) pkt)->
				entry_type = CONTINUE_TYPE;
			((काष्ठा cont_entry *) pkt)->entry_count = 1;

			((काष्ठा cont_entry *) pkt)->sys_define =
				(uपूर्णांक8_t) ha->req_ring_index;

			/* Setup packet address segment poपूर्णांकer. */
			dword_ptr =
				&((काष्ठा cont_entry *) pkt)->dseg_0_address;

			/* Load continuation entry data segments. */
			क्रम_each_sg(sg, s, remseg, cnt) अणु
				अगर (cnt == 7)
					अवरोध;
				*dword_ptr++ =
					cpu_to_le32(lower_32_bits(sg_dma_address(s)));
				*dword_ptr++ =
					cpu_to_le32(sg_dma_len(s));
				dprपूर्णांकk(1,
					"S/G Segment Cont. phys_addr=0x%x, "
					"len=0x%x\n",
					cpu_to_le32(lower_32_bits(sg_dma_address(s))),
					cpu_to_le32(sg_dma_len(s)));
			पूर्ण
			remseg -= cnt;
			dprपूर्णांकk(5, "qla1280_32bit_start_scsi: "
				"continuation packet data - "
				"scsi(%i:%i:%i)\n", SCSI_BUS_32(cmd),
				SCSI_TCN_32(cmd), SCSI_LUN_32(cmd));
			qla1280_dump_buffer(5, (अक्षर *)pkt,
					    REQUEST_ENTRY_SIZE);
		पूर्ण
	पूर्ण अन्यथा अणु	/* No data transfer at all */
		dprपूर्णांकk(5, "qla1280_32bit_start_scsi: No data, command "
			"packet data - \n");
		qla1280_dump_buffer(5, (अक्षर *)pkt, REQUEST_ENTRY_SIZE);
	पूर्ण
	dprपूर्णांकk(5, "qla1280_32bit_start_scsi: First IOCB block:\n");
	qla1280_dump_buffer(5, (अक्षर *)ha->request_ring_ptr,
			    REQUEST_ENTRY_SIZE);

	/* Adjust ring index. */
	ha->req_ring_index++;
	अगर (ha->req_ring_index == REQUEST_ENTRY_CNT) अणु
		ha->req_ring_index = 0;
		ha->request_ring_ptr = ha->request_ring;
	पूर्ण अन्यथा
		ha->request_ring_ptr++;

	/* Set chip new ring index. */
	dprपूर्णांकk(2, "qla1280_32bit_start_scsi: Wakeup RISC "
		"for pending command\n");
	sp->flags |= SRB_SENT;
	ha->actthपढ़ोs++;
	WRT_REG_WORD(&reg->mailbox4, ha->req_ring_index);

out:
	अगर (status)
		dprपूर्णांकk(2, "qla1280_32bit_start_scsi: **** FAILED ****\n");

	LEAVE("qla1280_32bit_start_scsi");

	वापस status;
पूर्ण
#पूर्ण_अगर

/*
 * qla1280_req_pkt
 *      Function is responsible क्रम locking ring and
 *      getting a zeroed out request packet.
 *
 * Input:
 *      ha  = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = failed to get slot.
 */
अटल request_t *
qla1280_req_pkt(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	request_t *pkt = शून्य;
	पूर्णांक cnt;
	uपूर्णांक32_t समयr;

	ENTER("qla1280_req_pkt");

	/*
	 * This can be called from पूर्णांकerrupt context, damn it!!!
	 */
	/* Wait क्रम 30 seconds क्रम slot. */
	क्रम (समयr = 15000000; समयr; समयr--) अणु
		अगर (ha->req_q_cnt > 0) अणु
			/* Calculate number of मुक्त request entries. */
			cnt = RD_REG_WORD(&reg->mailbox4);
			अगर (ha->req_ring_index < cnt)
				ha->req_q_cnt = cnt - ha->req_ring_index;
			अन्यथा
				ha->req_q_cnt =
					REQUEST_ENTRY_CNT - (ha->req_ring_index - cnt);
		पूर्ण

		/* Found empty request ring slot? */
		अगर (ha->req_q_cnt > 0) अणु
			ha->req_q_cnt--;
			pkt = ha->request_ring_ptr;

			/* Zero out packet. */
			स_रखो(pkt, 0, REQUEST_ENTRY_SIZE);

			/*
			 * How can this be right when we have a ring
			 * size of 512???
			 */
			/* Set प्रणाली defined field. */
			pkt->sys_define = (uपूर्णांक8_t) ha->req_ring_index;

			/* Set entry count. */
			pkt->entry_count = 1;

			अवरोध;
		पूर्ण

		udelay(2);	/* 10 */

		/* Check क्रम pending पूर्णांकerrupts. */
		qla1280_poll(ha);
	पूर्ण

	अगर (!pkt)
		dprपूर्णांकk(2, "qla1280_req_pkt: **** FAILED ****\n");
	अन्यथा
		dprपूर्णांकk(3, "qla1280_req_pkt: exiting normally\n");

	वापस pkt;
पूर्ण

/*
 * qla1280_isp_cmd
 *      Function is responsible क्रम modअगरying ISP input poपूर्णांकer.
 *      Releases ring lock.
 *
 * Input:
 *      ha  = adapter block poपूर्णांकer.
 */
अटल व्योम
qla1280_isp_cmd(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;

	ENTER("qla1280_isp_cmd");

	dprपूर्णांकk(5, "qla1280_isp_cmd: IOCB data:\n");
	qla1280_dump_buffer(5, (अक्षर *)ha->request_ring_ptr,
			    REQUEST_ENTRY_SIZE);

	/* Adjust ring index. */
	ha->req_ring_index++;
	अगर (ha->req_ring_index == REQUEST_ENTRY_CNT) अणु
		ha->req_ring_index = 0;
		ha->request_ring_ptr = ha->request_ring;
	पूर्ण अन्यथा
		ha->request_ring_ptr++;

	/*
	 * Update request index to mailbox4 (Request Queue In).
	 */
	WRT_REG_WORD(&reg->mailbox4, ha->req_ring_index);

	LEAVE("qla1280_isp_cmd");
पूर्ण

/****************************************************************************/
/*                        Interrupt Service Routine.                        */
/****************************************************************************/

/****************************************************************************
 *  qla1280_isr
 *      Calls I/O करोne on command completion.
 *
 * Input:
 *      ha           = adapter block poपूर्णांकer.
 *      करोne_q       = करोne queue.
 ****************************************************************************/
अटल व्योम
qla1280_isr(काष्ठा scsi_qla_host *ha, काष्ठा list_head *करोne_q)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	काष्ठा response *pkt;
	काष्ठा srb *sp = शून्य;
	uपूर्णांक16_t mailbox[MAILBOX_REGISTER_COUNT];
	uपूर्णांक16_t *wptr;
	uपूर्णांक32_t index;
	u16 istatus;

	ENTER("qla1280_isr");

	istatus = RD_REG_WORD(&reg->istatus);
	अगर (!(istatus & (RISC_INT | PCI_INT)))
		वापस;

	/* Save mailbox रेजिस्टर 5 */
	mailbox[5] = RD_REG_WORD(&reg->mailbox5);

	/* Check क्रम mailbox पूर्णांकerrupt. */

	mailbox[0] = RD_REG_WORD_dmasync(&reg->semaphore);

	अगर (mailbox[0] & BIT_0) अणु
		/* Get mailbox data. */
		/* dprपूर्णांकk(1, "qla1280_isr: In Get mailbox data \n"); */

		wptr = &mailbox[0];
		*wptr++ = RD_REG_WORD(&reg->mailbox0);
		*wptr++ = RD_REG_WORD(&reg->mailbox1);
		*wptr = RD_REG_WORD(&reg->mailbox2);
		अगर (mailbox[0] != MBA_SCSI_COMPLETION) अणु
			wptr++;
			*wptr++ = RD_REG_WORD(&reg->mailbox3);
			*wptr++ = RD_REG_WORD(&reg->mailbox4);
			wptr++;
			*wptr++ = RD_REG_WORD(&reg->mailbox6);
			*wptr = RD_REG_WORD(&reg->mailbox7);
		पूर्ण

		/* Release mailbox रेजिस्टरs. */

		WRT_REG_WORD(&reg->semaphore, 0);
		WRT_REG_WORD(&reg->host_cmd, HC_CLR_RISC_INT);

		dprपूर्णांकk(5, "qla1280_isr: mailbox interrupt mailbox[0] = 0x%x",
			mailbox[0]);

		/* Handle asynchronous event */
		चयन (mailbox[0]) अणु
		हाल MBA_SCSI_COMPLETION:	/* Response completion */
			dprपूर्णांकk(5, "qla1280_isr: mailbox SCSI response "
				"completion\n");

			अगर (ha->flags.online) अणु
				/* Get outstanding command index. */
				index = mailbox[2] << 16 | mailbox[1];

				/* Validate handle. */
				अगर (index < MAX_OUTSTANDING_COMMANDS)
					sp = ha->outstanding_cmds[index];
				अन्यथा
					sp = शून्य;

				अगर (sp) अणु
					/* Free outstanding command slot. */
					ha->outstanding_cmds[index] = शून्य;

					/* Save ISP completion status */
					CMD_RESULT(sp->cmd) = 0;
					CMD_HANDLE(sp->cmd) = COMPLETED_HANDLE;

					/* Place block on करोne queue */
					list_add_tail(&sp->list, करोne_q);
				पूर्ण अन्यथा अणु
					/*
					 * If we get here we have a real problem!
					 */
					prपूर्णांकk(KERN_WARNING
					       "qla1280: ISP invalid handle\n");
				पूर्ण
			पूर्ण
			अवरोध;

		हाल MBA_BUS_RESET:	/* SCSI Bus Reset */
			ha->flags.reset_marker = 1;
			index = mailbox[6] & BIT_0;
			ha->bus_settings[index].reset_marker = 1;

			prपूर्णांकk(KERN_DEBUG "qla1280_isr(): index %i "
			       "asynchronous BUS_RESET\n", index);
			अवरोध;

		हाल MBA_SYSTEM_ERR:	/* System Error */
			prपूर्णांकk(KERN_WARNING
			       "qla1280: ISP System Error - mbx1=%xh, mbx2="
			       "%xh, mbx3=%xh\n", mailbox[1], mailbox[2],
			       mailbox[3]);
			अवरोध;

		हाल MBA_REQ_TRANSFER_ERR:	/* Request Transfer Error */
			prपूर्णांकk(KERN_WARNING
			       "qla1280: ISP Request Transfer Error\n");
			अवरोध;

		हाल MBA_RSP_TRANSFER_ERR:	/* Response Transfer Error */
			prपूर्णांकk(KERN_WARNING
			       "qla1280: ISP Response Transfer Error\n");
			अवरोध;

		हाल MBA_WAKEUP_THRES:	/* Request Queue Wake-up */
			dprपूर्णांकk(2, "qla1280_isr: asynchronous WAKEUP_THRES\n");
			अवरोध;

		हाल MBA_TIMEOUT_RESET:	/* Execution Timeout Reset */
			dprपूर्णांकk(2,
				"qla1280_isr: asynchronous TIMEOUT_RESET\n");
			अवरोध;

		हाल MBA_DEVICE_RESET:	/* Bus Device Reset */
			prपूर्णांकk(KERN_INFO "qla1280_isr(): asynchronous "
			       "BUS_DEVICE_RESET\n");

			ha->flags.reset_marker = 1;
			index = mailbox[6] & BIT_0;
			ha->bus_settings[index].reset_marker = 1;
			अवरोध;

		हाल MBA_BUS_MODE_CHANGE:
			dprपूर्णांकk(2,
				"qla1280_isr: asynchronous BUS_MODE_CHANGE\n");
			अवरोध;

		शेष:
			/* dprपूर्णांकk(1, "qla1280_isr: default case of switch MB \n"); */
			अगर (mailbox[0] < MBA_ASYNC_EVENT) अणु
				wptr = &mailbox[0];
				स_नकल((uपूर्णांक16_t *) ha->mailbox_out, wptr,
				       MAILBOX_REGISTER_COUNT *
				       माप(uपूर्णांक16_t));

				अगर(ha->mailbox_रुको != शून्य)
					complete(ha->mailbox_रुको);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		WRT_REG_WORD(&reg->host_cmd, HC_CLR_RISC_INT);
	पूर्ण

	/*
	 * We will receive पूर्णांकerrupts during mailbox testing prior to
	 * the card being marked online, hence the द्विगुन check.
	 */
	अगर (!(ha->flags.online && !ha->mailbox_रुको)) अणु
		dprपूर्णांकk(2, "qla1280_isr: Response pointer Error\n");
		जाओ out;
	पूर्ण

	अगर (mailbox[5] >= RESPONSE_ENTRY_CNT)
		जाओ out;

	जबतक (ha->rsp_ring_index != mailbox[5]) अणु
		pkt = ha->response_ring_ptr;

		dprपूर्णांकk(5, "qla1280_isr: ha->rsp_ring_index = 0x%x, mailbox[5]"
			" = 0x%x\n", ha->rsp_ring_index, mailbox[5]);
		dprपूर्णांकk(5,"qla1280_isr: response packet data\n");
		qla1280_dump_buffer(5, (अक्षर *)pkt, RESPONSE_ENTRY_SIZE);

		अगर (pkt->entry_type == STATUS_TYPE) अणु
			अगर ((le16_to_cpu(pkt->scsi_status) & 0xff)
			    || pkt->comp_status || pkt->entry_status) अणु
				dprपूर्णांकk(2, "qla1280_isr: ha->rsp_ring_index = "
					"0x%x mailbox[5] = 0x%x, comp_status "
					"= 0x%x, scsi_status = 0x%x\n",
					ha->rsp_ring_index, mailbox[5],
					le16_to_cpu(pkt->comp_status),
					le16_to_cpu(pkt->scsi_status));
			पूर्ण
		पूर्ण अन्यथा अणु
			dprपूर्णांकk(2, "qla1280_isr: ha->rsp_ring_index = "
				"0x%x, mailbox[5] = 0x%x\n",
				ha->rsp_ring_index, mailbox[5]);
			dprपूर्णांकk(2, "qla1280_isr: response packet data\n");
			qla1280_dump_buffer(2, (अक्षर *)pkt,
					    RESPONSE_ENTRY_SIZE);
		पूर्ण

		अगर (pkt->entry_type == STATUS_TYPE || pkt->entry_status) अणु
			dprपूर्णांकk(2, "status: Cmd %p, handle %i\n",
				ha->outstanding_cmds[pkt->handle]->cmd,
				pkt->handle);
			अगर (pkt->entry_type == STATUS_TYPE)
				qla1280_status_entry(ha, pkt, करोne_q);
			अन्यथा
				qla1280_error_entry(ha, pkt, करोne_q);
			/* Adjust ring index. */
			ha->rsp_ring_index++;
			अगर (ha->rsp_ring_index == RESPONSE_ENTRY_CNT) अणु
				ha->rsp_ring_index = 0;
				ha->response_ring_ptr =	ha->response_ring;
			पूर्ण अन्यथा
				ha->response_ring_ptr++;
			WRT_REG_WORD(&reg->mailbox5, ha->rsp_ring_index);
		पूर्ण
	पूर्ण
	
 out:
	LEAVE("qla1280_isr");
पूर्ण

/*
 *  qla1280_rst_aen
 *      Processes asynchronous reset.
 *
 * Input:
 *      ha  = adapter block poपूर्णांकer.
 */
अटल व्योम
qla1280_rst_aen(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक8_t bus;

	ENTER("qla1280_rst_aen");

	अगर (ha->flags.online && !ha->flags.reset_active &&
	    !ha->flags.पात_isp_active) अणु
		ha->flags.reset_active = 1;
		जबतक (ha->flags.reset_marker) अणु
			/* Issue marker command. */
			ha->flags.reset_marker = 0;
			क्रम (bus = 0; bus < ha->ports &&
				     !ha->flags.reset_marker; bus++) अणु
				अगर (ha->bus_settings[bus].reset_marker) अणु
					ha->bus_settings[bus].reset_marker = 0;
					qla1280_marker(ha, bus, 0, 0,
						       MK_SYNC_ALL);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	LEAVE("qla1280_rst_aen");
पूर्ण


/*
 *  qla1280_status_entry
 *      Processes received ISP status entry.
 *
 * Input:
 *      ha           = adapter block poपूर्णांकer.
 *      pkt          = entry poपूर्णांकer.
 *      करोne_q       = करोne queue.
 */
अटल व्योम
qla1280_status_entry(काष्ठा scsi_qla_host *ha, काष्ठा response *pkt,
		     काष्ठा list_head *करोne_q)
अणु
	पूर्णांक sense_sz;
	काष्ठा srb *sp;
	काष्ठा scsi_cmnd *cmd;
	uपूर्णांक32_t handle = le32_to_cpu(pkt->handle);
	uपूर्णांक16_t scsi_status = le16_to_cpu(pkt->scsi_status);
	uपूर्णांक16_t comp_status = le16_to_cpu(pkt->comp_status);

	ENTER("qla1280_status_entry");

	/* Validate handle. */
	अगर (handle < MAX_OUTSTANDING_COMMANDS)
		sp = ha->outstanding_cmds[handle];
	अन्यथा
		sp = शून्य;

	अगर (!sp) अणु
		prपूर्णांकk(KERN_WARNING "qla1280: Status Entry invalid handle\n");
		जाओ out;
	पूर्ण

	/* Free outstanding command slot. */
	ha->outstanding_cmds[handle] = शून्य;

	cmd = sp->cmd;

	अगर (comp_status || scsi_status) अणु
		dprपूर्णांकk(3, "scsi: comp_status = 0x%x, scsi_status = "
			"0x%x, handle = 0x%x\n", comp_status,
			scsi_status, handle);
	पूर्ण

	/* Target busy or queue full */
	अगर ((scsi_status & 0xFF) == SAM_STAT_TASK_SET_FULL ||
	    (scsi_status & 0xFF) == SAM_STAT_BUSY) अणु
		CMD_RESULT(cmd) = scsi_status & 0xff;
	पूर्ण अन्यथा अणु

		/* Save ISP completion status */
		CMD_RESULT(cmd) = qla1280_वापस_status(pkt, cmd);

		अगर (scsi_status & SAM_STAT_CHECK_CONDITION) अणु
			अगर (comp_status != CS_ARS_FAILED) अणु
				uपूर्णांक16_t req_sense_length =
					le16_to_cpu(pkt->req_sense_length);
				अगर (req_sense_length < CMD_SNSLEN(cmd))
					sense_sz = req_sense_length;
				अन्यथा
					/*
					 * scsi_cmnd->sense_buffer is
					 * 64 bytes, why only copy 63?
					 * This looks wrong! /Jes
					 */
					sense_sz = CMD_SNSLEN(cmd) - 1;

				स_नकल(cmd->sense_buffer,
				       &pkt->req_sense_data, sense_sz);
			पूर्ण अन्यथा
				sense_sz = 0;
			स_रखो(cmd->sense_buffer + sense_sz, 0,
			       SCSI_SENSE_BUFFERSIZE - sense_sz);

			dprपूर्णांकk(2, "qla1280_status_entry: Check "
				"condition Sense data, b %i, t %i, "
				"l %i\n", SCSI_BUS_32(cmd), SCSI_TCN_32(cmd),
				SCSI_LUN_32(cmd));
			अगर (sense_sz)
				qla1280_dump_buffer(2,
						    (अक्षर *)cmd->sense_buffer,
						    sense_sz);
		पूर्ण
	पूर्ण

	CMD_HANDLE(sp->cmd) = COMPLETED_HANDLE;

	/* Place command on करोne queue. */
	list_add_tail(&sp->list, करोne_q);
 out:
	LEAVE("qla1280_status_entry");
पूर्ण

/*
 *  qla1280_error_entry
 *      Processes error entry.
 *
 * Input:
 *      ha           = adapter block poपूर्णांकer.
 *      pkt          = entry poपूर्णांकer.
 *      करोne_q       = करोne queue.
 */
अटल व्योम
qla1280_error_entry(काष्ठा scsi_qla_host *ha, काष्ठा response *pkt,
		    काष्ठा list_head *करोne_q)
अणु
	काष्ठा srb *sp;
	uपूर्णांक32_t handle = le32_to_cpu(pkt->handle);

	ENTER("qla1280_error_entry");

	अगर (pkt->entry_status & BIT_3)
		dprपूर्णांकk(2, "qla1280_error_entry: BAD PAYLOAD flag error\n");
	अन्यथा अगर (pkt->entry_status & BIT_2)
		dprपूर्णांकk(2, "qla1280_error_entry: BAD HEADER flag error\n");
	अन्यथा अगर (pkt->entry_status & BIT_1)
		dprपूर्णांकk(2, "qla1280_error_entry: FULL flag error\n");
	अन्यथा
		dprपूर्णांकk(2, "qla1280_error_entry: UNKNOWN flag error\n");

	/* Validate handle. */
	अगर (handle < MAX_OUTSTANDING_COMMANDS)
		sp = ha->outstanding_cmds[handle];
	अन्यथा
		sp = शून्य;

	अगर (sp) अणु
		/* Free outstanding command slot. */
		ha->outstanding_cmds[handle] = शून्य;

		/* Bad payload or header */
		अगर (pkt->entry_status & (BIT_3 + BIT_2)) अणु
			/* Bad payload or header, set error status. */
			/* CMD_RESULT(sp->cmd) = CS_BAD_PAYLOAD; */
			CMD_RESULT(sp->cmd) = DID_ERROR << 16;
		पूर्ण अन्यथा अगर (pkt->entry_status & BIT_1) अणु	/* FULL flag */
			CMD_RESULT(sp->cmd) = DID_BUS_BUSY << 16;
		पूर्ण अन्यथा अणु
			/* Set error status. */
			CMD_RESULT(sp->cmd) = DID_ERROR << 16;
		पूर्ण

		CMD_HANDLE(sp->cmd) = COMPLETED_HANDLE;

		/* Place command on करोne queue. */
		list_add_tail(&sp->list, करोne_q);
	पूर्ण
#अगर_घोषित QLA_64BIT_PTR
	अन्यथा अगर (pkt->entry_type == COMMAND_A64_TYPE) अणु
		prपूर्णांकk(KERN_WARNING "!qla1280: Error Entry invalid handle");
	पूर्ण
#पूर्ण_अगर

	LEAVE("qla1280_error_entry");
पूर्ण

/*
 *  qla1280_पात_isp
 *      Resets ISP and पातs all outstanding commands.
 *
 * Input:
 *      ha           = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
अटल पूर्णांक
qla1280_पात_isp(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा device_reg __iomem *reg = ha->iobase;
	काष्ठा srb *sp;
	पूर्णांक status = 0;
	पूर्णांक cnt;
	पूर्णांक bus;

	ENTER("qla1280_abort_isp");

	अगर (ha->flags.पात_isp_active || !ha->flags.online)
		जाओ out;
	
	ha->flags.पात_isp_active = 1;

	/* Disable ISP पूर्णांकerrupts. */
	qla1280_disable_पूर्णांकrs(ha);
	WRT_REG_WORD(&reg->host_cmd, HC_PAUSE_RISC);
	RD_REG_WORD(&reg->id_l);

	prपूर्णांकk(KERN_INFO "scsi(%li): dequeuing outstanding commands\n",
	       ha->host_no);
	/* Dequeue all commands in outstanding command list. */
	क्रम (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS; cnt++) अणु
		काष्ठा scsi_cmnd *cmd;
		sp = ha->outstanding_cmds[cnt];
		अगर (sp) अणु
			cmd = sp->cmd;
			CMD_RESULT(cmd) = DID_RESET << 16;
			CMD_HANDLE(cmd) = COMPLETED_HANDLE;
			ha->outstanding_cmds[cnt] = शून्य;
			list_add_tail(&sp->list, &ha->करोne_q);
		पूर्ण
	पूर्ण

	qla1280_करोne(ha);

	status = qla1280_load_firmware(ha);
	अगर (status)
		जाओ out;

	/* Setup adapter based on NVRAM parameters. */
	qla1280_nvram_config (ha);

	status = qla1280_init_rings(ha);
	अगर (status)
		जाओ out;
		
	/* Issue SCSI reset. */
	क्रम (bus = 0; bus < ha->ports; bus++)
		qla1280_bus_reset(ha, bus);
		
	ha->flags.पात_isp_active = 0;
 out:
	अगर (status) अणु
		prपूर्णांकk(KERN_WARNING
		       "qla1280: ISP error recovery failed, board disabled");
		qla1280_reset_adapter(ha);
		dprपूर्णांकk(2, "qla1280_abort_isp: **** FAILED ****\n");
	पूर्ण

	LEAVE("qla1280_abort_isp");
	वापस status;
पूर्ण


/*
 * qla1280_debounce_रेजिस्टर
 *      Debounce रेजिस्टर.
 *
 * Input:
 *      port = रेजिस्टर address.
 *
 * Returns:
 *      रेजिस्टर value.
 */
अटल u16
qla1280_debounce_रेजिस्टर(अस्थिर u16 __iomem * addr)
अणु
	अस्थिर u16 ret;
	अस्थिर u16 ret2;

	ret = RD_REG_WORD(addr);
	ret2 = RD_REG_WORD(addr);

	अगर (ret == ret2)
		वापस ret;

	करो अणु
		cpu_relax();
		ret = RD_REG_WORD(addr);
		ret2 = RD_REG_WORD(addr);
	पूर्ण जबतक (ret != ret2);

	वापस ret;
पूर्ण


/************************************************************************
 * qla1280_check_क्रम_dead_scsi_bus                                      *
 *                                                                      *
 *    This routine checks क्रम a dead SCSI bus                           *
 ************************************************************************/
#घोषणा SET_SXP_BANK            0x0100
#घोषणा SCSI_PHASE_INVALID      0x87FF
अटल पूर्णांक
qla1280_check_क्रम_dead_scsi_bus(काष्ठा scsi_qla_host *ha, अचिन्हित पूर्णांक bus)
अणु
	uपूर्णांक16_t config_reg, scsi_control;
	काष्ठा device_reg __iomem *reg = ha->iobase;

	अगर (ha->bus_settings[bus].scsi_bus_dead) अणु
		WRT_REG_WORD(&reg->host_cmd, HC_PAUSE_RISC);
		config_reg = RD_REG_WORD(&reg->cfg_1);
		WRT_REG_WORD(&reg->cfg_1, SET_SXP_BANK);
		scsi_control = RD_REG_WORD(&reg->scsiControlPins);
		WRT_REG_WORD(&reg->cfg_1, config_reg);
		WRT_REG_WORD(&reg->host_cmd, HC_RELEASE_RISC);

		अगर (scsi_control == SCSI_PHASE_INVALID) अणु
			ha->bus_settings[bus].scsi_bus_dead = 1;
			वापस 1;	/* bus is dead */
		पूर्ण अन्यथा अणु
			ha->bus_settings[bus].scsi_bus_dead = 0;
			ha->bus_settings[bus].failed_reset_count = 0;
		पूर्ण
	पूर्ण
	वापस 0;		/* bus is not dead */
पूर्ण

अटल व्योम
qla1280_get_target_parameters(काष्ठा scsi_qla_host *ha,
			      काष्ठा scsi_device *device)
अणु
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	पूर्णांक bus, target, lun;

	bus = device->channel;
	target = device->id;
	lun = device->lun;


	mb[0] = MBC_GET_TARGET_PARAMETERS;
	mb[1] = (uपूर्णांक16_t) (bus ? target | BIT_7 : target);
	mb[1] <<= 8;
	qla1280_mailbox_command(ha, BIT_6 | BIT_3 | BIT_2 | BIT_1 | BIT_0,
				&mb[0]);

	prपूर्णांकk(KERN_INFO "scsi(%li:%d:%d:%d):", ha->host_no, bus, target, lun);

	अगर (mb[3] != 0) अणु
		prपूर्णांकk(KERN_CONT " Sync: period %d, offset %d",
		       (mb[3] & 0xff), (mb[3] >> 8));
		अगर (mb[2] & BIT_13)
			prपूर्णांकk(KERN_CONT ", Wide");
		अगर ((mb[2] & BIT_5) && ((mb[6] >> 8) & 0xff) >= 2)
			prपूर्णांकk(KERN_CONT ", DT");
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_CONT " Async");

	अगर (device->simple_tags)
		prपूर्णांकk(KERN_CONT ", Tagged queuing: depth %d", device->queue_depth);
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण


#अगर DEBUG_QLA1280
अटल व्योम
__qla1280_dump_buffer(अक्षर *b, पूर्णांक size)
अणु
	पूर्णांक cnt;
	u8 c;

	prपूर्णांकk(KERN_DEBUG " 0   1   2   3   4   5   6   7   8   9   Ah  "
	       "Bh  Ch  Dh  Eh  Fh\n");
	prपूर्णांकk(KERN_DEBUG "---------------------------------------------"
	       "------------------\n");

	क्रम (cnt = 0; cnt < size;) अणु
		c = *b++;

		prपूर्णांकk("0x%02x", c);
		cnt++;
		अगर (!(cnt % 16))
			prपूर्णांकk("\n");
		अन्यथा
			prपूर्णांकk(" ");
	पूर्ण
	अगर (cnt % 16)
		prपूर्णांकk("\n");
पूर्ण

/**************************************************************************
 *   ql1280_prपूर्णांक_scsi_cmd
 *
 **************************************************************************/
अटल व्योम
__qla1280_prपूर्णांक_scsi_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_qla_host *ha;
	काष्ठा Scsi_Host *host = CMD_HOST(cmd);
	काष्ठा srb *sp;
	/* काष्ठा scatterlist *sg; */

	पूर्णांक i;
	ha = (काष्ठा scsi_qla_host *)host->hostdata;

	sp = (काष्ठा srb *)CMD_SP(cmd);
	prपूर्णांकk("SCSI Command @= 0x%p, Handle=0x%p\n", cmd, CMD_HANDLE(cmd));
	prपूर्णांकk("  chan=%d, target = 0x%02x, lun = 0x%02x, cmd_len = 0x%02x\n",
	       SCSI_BUS_32(cmd), SCSI_TCN_32(cmd), SCSI_LUN_32(cmd),
	       CMD_CDBLEN(cmd));
	prपूर्णांकk(" CDB = ");
	क्रम (i = 0; i < cmd->cmd_len; i++) अणु
		prपूर्णांकk("0x%02x ", cmd->cmnd[i]);
	पूर्ण
	prपूर्णांकk("  seg_cnt =%d\n", scsi_sg_count(cmd));
	prपूर्णांकk("  request buffer=0x%p, request buffer len=0x%x\n",
	       scsi_sglist(cmd), scsi_bufflen(cmd));
	/* अगर (cmd->use_sg)
	   अणु
	   sg = (काष्ठा scatterlist *) cmd->request_buffer;
	   prपूर्णांकk("  SG buffer: \n");
	   qla1280_dump_buffer(1, (अक्षर *)sg, (cmd->use_sg*माप(काष्ठा scatterlist)));
	   पूर्ण */
	prपूर्णांकk("  tag=%d, transfersize=0x%x \n",
	       cmd->tag, cmd->transfersize);
	prपूर्णांकk("  SP=0x%p\n", CMD_SP(cmd));
	prपूर्णांकk(" underflow size = 0x%x, direction=0x%x\n",
	       cmd->underflow, cmd->sc_data_direction);
पूर्ण

/**************************************************************************
 *   ql1280_dump_device
 *
 **************************************************************************/
अटल व्योम
ql1280_dump_device(काष्ठा scsi_qla_host *ha)
अणु

	काष्ठा scsi_cmnd *cp;
	काष्ठा srb *sp;
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "Outstanding Commands on controller:\n");

	क्रम (i = 0; i < MAX_OUTSTANDING_COMMANDS; i++) अणु
		अगर ((sp = ha->outstanding_cmds[i]) == शून्य)
			जारी;
		अगर ((cp = sp->cmd) == शून्य)
			जारी;
		qla1280_prपूर्णांक_scsi_cmd(1, cp);
	पूर्ण
पूर्ण
#पूर्ण_अगर


क्रमागत tokens अणु
	TOKEN_NVRAM,
	TOKEN_SYNC,
	TOKEN_WIDE,
	TOKEN_PPR,
	TOKEN_VERBOSE,
	TOKEN_DEBUG,
पूर्ण;

काष्ठा setup_tokens अणु
	अक्षर *token;
	पूर्णांक val;
पूर्ण;

अटल काष्ठा setup_tokens setup_token[] __initdata = 
अणु
	अणु "nvram", TOKEN_NVRAM पूर्ण,
	अणु "sync", TOKEN_SYNC पूर्ण,
	अणु "wide", TOKEN_WIDE पूर्ण,
	अणु "ppr", TOKEN_PPR पूर्ण,
	अणु "verbose", TOKEN_VERBOSE पूर्ण,
	अणु "debug", TOKEN_DEBUG पूर्ण,
पूर्ण;


/**************************************************************************
 *   qla1280_setup
 *
 *   Handle boot parameters. This really needs to be changed so one
 *   can specअगरy per adapter parameters.
 **************************************************************************/
अटल पूर्णांक __init
qla1280_setup(अक्षर *s)
अणु
	अक्षर *cp, *ptr;
	अचिन्हित दीर्घ val;
	पूर्णांक toke;

	cp = s;

	जबतक (cp && (ptr = म_अक्षर(cp, ':'))) अणु
		ptr++;
		अगर (!म_भेद(ptr, "yes")) अणु
			val = 0x10000;
			ptr += 3;
		पूर्ण अन्यथा अगर (!म_भेद(ptr, "no")) अणु
 			val = 0;
			ptr += 2;
		पूर्ण अन्यथा
			val = simple_म_से_अदीर्घ(ptr, &ptr, 0);

		चयन ((toke = qla1280_get_token(cp))) अणु
		हाल TOKEN_NVRAM:
			अगर (!val)
				driver_setup.no_nvram = 1;
			अवरोध;
		हाल TOKEN_SYNC:
			अगर (!val)
				driver_setup.no_sync = 1;
			अन्यथा अगर (val != 0x10000)
				driver_setup.sync_mask = val;
			अवरोध;
		हाल TOKEN_WIDE:
			अगर (!val)
				driver_setup.no_wide = 1;
			अन्यथा अगर (val != 0x10000)
				driver_setup.wide_mask = val;
			अवरोध;
		हाल TOKEN_PPR:
			अगर (!val)
				driver_setup.no_ppr = 1;
			अन्यथा अगर (val != 0x10000)
				driver_setup.ppr_mask = val;
			अवरोध;
		हाल TOKEN_VERBOSE:
			qla1280_verbose = val;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "qla1280: unknown boot option %s\n",
			       cp);
		पूर्ण

		cp = म_अक्षर(ptr, ';');
		अगर (cp)
			cp++;
		अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण


अटल पूर्णांक __init
qla1280_get_token(अक्षर *str)
अणु
	अक्षर *sep;
	दीर्घ ret = -1;
	पूर्णांक i;

	sep = म_अक्षर(str, ':');

	अगर (sep) अणु
		क्रम (i = 0; i < ARRAY_SIZE(setup_token); i++) अणु
			अगर (!म_भेदन(setup_token[i].token, str, (sep - str))) अणु
				ret =  setup_token[i].val;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


अटल काष्ठा scsi_host_ढाँचा qla1280_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= "qla1280",
	.name			= "Qlogic ISP 1280/12160",
	.info			= qla1280_info,
	.slave_configure	= qla1280_slave_configure,
	.queuecommand		= qla1280_queuecommand,
	.eh_पात_handler	= qla1280_eh_पात,
	.eh_device_reset_handler= qla1280_eh_device_reset,
	.eh_bus_reset_handler	= qla1280_eh_bus_reset,
	.eh_host_reset_handler	= qla1280_eh_adapter_reset,
	.bios_param		= qla1280_biosparam,
	.can_queue		= MAX_OUTSTANDING_COMMANDS,
	.this_id		= -1,
	.sg_tablesize		= SG_ALL,
पूर्ण;


अटल पूर्णांक
qla1280_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक devnum = id->driver_data;
	काष्ठा qla_boards *bdp = &ql1280_board_tbl[devnum];
	काष्ठा Scsi_Host *host;
	काष्ठा scsi_qla_host *ha;
	पूर्णांक error = -ENODEV;

	/* Bypass all AMI SUBSYS VENDOR IDs */
	अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_AMI) अणु
		prपूर्णांकk(KERN_INFO
		       "qla1280: Skipping AMI SubSys Vendor ID Chip\n");
		जाओ error;
	पूर्ण

	prपूर्णांकk(KERN_INFO "qla1280: %s found on PCI bus %i, dev %i\n",
	       bdp->name, pdev->bus->number, PCI_SLOT(pdev->devfn));
	
	अगर (pci_enable_device(pdev)) अणु
		prपूर्णांकk(KERN_WARNING
		       "qla1280: Failed to enabled pci device, aborting.\n");
		जाओ error;
	पूर्ण

	pci_set_master(pdev);

	error = -ENOMEM;
	host = scsi_host_alloc(&qla1280_driver_ढाँचा, माप(*ha));
	अगर (!host) अणु
		prपूर्णांकk(KERN_WARNING
		       "qla1280: Failed to register host, aborting.\n");
		जाओ error_disable_device;
	पूर्ण

	ha = (काष्ठा scsi_qla_host *)host->hostdata;
	स_रखो(ha, 0, माप(काष्ठा scsi_qla_host));

	ha->pdev = pdev;
	ha->devnum = devnum;	/* specअगरies microcode load address */

#अगर_घोषित QLA_64BIT_PTR
	अगर (dma_set_mask_and_coherent(&ha->pdev->dev, DMA_BIT_MASK(64))) अणु
		अगर (dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(32))) अणु
			prपूर्णांकk(KERN_WARNING "scsi(%li): Unable to set a "
			       "suitable DMA mask - aborting\n", ha->host_no);
			error = -ENODEV;
			जाओ error_put_host;
		पूर्ण
	पूर्ण अन्यथा
		dprपूर्णांकk(2, "scsi(%li): 64 Bit PCI Addressing Enabled\n",
			ha->host_no);
#अन्यथा
	अगर (dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_WARNING "scsi(%li): Unable to set a "
		       "suitable DMA mask - aborting\n", ha->host_no);
		error = -ENODEV;
		जाओ error_put_host;
	पूर्ण
#पूर्ण_अगर

	ha->request_ring = dma_alloc_coherent(&ha->pdev->dev,
			((REQUEST_ENTRY_CNT + 1) * माप(request_t)),
			&ha->request_dma, GFP_KERNEL);
	अगर (!ha->request_ring) अणु
		prपूर्णांकk(KERN_INFO "qla1280: Failed to get request memory\n");
		जाओ error_put_host;
	पूर्ण

	ha->response_ring = dma_alloc_coherent(&ha->pdev->dev,
			((RESPONSE_ENTRY_CNT + 1) * माप(काष्ठा response)),
			&ha->response_dma, GFP_KERNEL);
	अगर (!ha->response_ring) अणु
		prपूर्णांकk(KERN_INFO "qla1280: Failed to get response memory\n");
		जाओ error_मुक्त_request_ring;
	पूर्ण

	ha->ports = bdp->numPorts;

	ha->host = host;
	ha->host_no = host->host_no;

	host->irq = pdev->irq;
	host->max_channel = bdp->numPorts - 1;
	host->max_lun = MAX_LUNS - 1;
	host->max_id = MAX_TARGETS;
	host->max_sectors = 1024;
	host->unique_id = host->host_no;

	error = -ENODEV;

#अगर MEMORY_MAPPED_IO
	ha->mmpbase = pci_ioremap_bar(ha->pdev, 1);
	अगर (!ha->mmpbase) अणु
		prपूर्णांकk(KERN_INFO "qla1280: Unable to map I/O memory\n");
		जाओ error_मुक्त_response_ring;
	पूर्ण

	host->base = (अचिन्हित दीर्घ)ha->mmpbase;
	ha->iobase = (काष्ठा device_reg __iomem *)ha->mmpbase;
#अन्यथा
	host->io_port = pci_resource_start(ha->pdev, 0);
	अगर (!request_region(host->io_port, 0xff, "qla1280")) अणु
		prपूर्णांकk(KERN_INFO "qla1280: Failed to reserve i/o region "
				 "0x%04lx-0x%04lx - already in use\n",
		       host->io_port, host->io_port + 0xff);
		जाओ error_मुक्त_response_ring;
	पूर्ण

	ha->iobase = (काष्ठा device_reg *)host->io_port;
#पूर्ण_अगर

	INIT_LIST_HEAD(&ha->करोne_q);

	/* Disable ISP पूर्णांकerrupts. */
	qla1280_disable_पूर्णांकrs(ha);

	अगर (request_irq(pdev->irq, qla1280_पूर्णांकr_handler, IRQF_SHARED,
				"qla1280", ha)) अणु
		prपूर्णांकk("qla1280 : Failed to reserve interrupt %d already "
		       "in use\n", pdev->irq);
		जाओ error_release_region;
	पूर्ण

	/* load the F/W, पढ़ो paramaters, and init the H/W */
	अगर (qla1280_initialize_adapter(ha)) अणु
		prपूर्णांकk(KERN_INFO "qla1x160: Failed to initialize adapter\n");
		जाओ error_मुक्त_irq;
	पूर्ण

	/* set our host ID  (need to करो something about our two IDs) */
	host->this_id = ha->bus_settings[0].id;

	pci_set_drvdata(pdev, host);

	error = scsi_add_host(host, &pdev->dev);
	अगर (error)
		जाओ error_disable_adapter;
	scsi_scan_host(host);

	वापस 0;

 error_disable_adapter:
	qla1280_disable_पूर्णांकrs(ha);
 error_मुक्त_irq:
	मुक्त_irq(pdev->irq, ha);
 error_release_region:
#अगर MEMORY_MAPPED_IO
	iounmap(ha->mmpbase);
#अन्यथा
	release_region(host->io_port, 0xff);
#पूर्ण_अगर
 error_मुक्त_response_ring:
	dma_मुक्त_coherent(&ha->pdev->dev,
			((RESPONSE_ENTRY_CNT + 1) * माप(काष्ठा response)),
			ha->response_ring, ha->response_dma);
 error_मुक्त_request_ring:
	dma_मुक्त_coherent(&ha->pdev->dev,
			((REQUEST_ENTRY_CNT + 1) * माप(request_t)),
			ha->request_ring, ha->request_dma);
 error_put_host:
	scsi_host_put(host);
 error_disable_device:
	pci_disable_device(pdev);
 error:
	वापस error;
पूर्ण


अटल व्योम
qla1280_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा scsi_qla_host *ha = (काष्ठा scsi_qla_host *)host->hostdata;

	scsi_हटाओ_host(host);

	qla1280_disable_पूर्णांकrs(ha);

	मुक्त_irq(pdev->irq, ha);

#अगर MEMORY_MAPPED_IO
	iounmap(ha->mmpbase);
#अन्यथा
	release_region(host->io_port, 0xff);
#पूर्ण_अगर

	dma_मुक्त_coherent(&ha->pdev->dev,
			((REQUEST_ENTRY_CNT + 1) * (माप(request_t))),
			ha->request_ring, ha->request_dma);
	dma_मुक्त_coherent(&ha->pdev->dev,
			((RESPONSE_ENTRY_CNT + 1) * (माप(काष्ठा response))),
			ha->response_ring, ha->response_dma);

	pci_disable_device(pdev);

	scsi_host_put(host);
पूर्ण

अटल काष्ठा pci_driver qla1280_pci_driver = अणु
	.name		= "qla1280",
	.id_table	= qla1280_pci_tbl,
	.probe		= qla1280_probe_one,
	.हटाओ		= qla1280_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init
qla1280_init(व्योम)
अणु
	अगर (माप(काष्ठा srb) > माप(काष्ठा scsi_poपूर्णांकer)) अणु
		prपूर्णांकk(KERN_WARNING
		       "qla1280: struct srb too big, aborting\n");
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित MODULE
	/*
	 * If we are called as a module, the qla1280 poपूर्णांकer may not be null
	 * and it would poपूर्णांक to our bootup string, just like on the lilo
	 * command line.  IF not शून्य, then process this config string with
	 * qla1280_setup
	 *
	 * Boot समय Options
	 * To add options at boot समय add a line to your lilo.conf file like:
	 * append="qla1280=verbose,max_tags:{{255,255,255,255},{255,255,255,255}}"
	 * which will result in the first four devices on the first two
	 * controllers being set to a tagged queue depth of 32.
	 */
	अगर (qla1280)
		qla1280_setup(qla1280);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&qla1280_pci_driver);
पूर्ण

अटल व्योम __निकास
qla1280_निकास(व्योम)
अणु
	पूर्णांक i;

	pci_unरेजिस्टर_driver(&qla1280_pci_driver);
	/* release any allocated firmware images */
	क्रम (i = 0; i < QL_NUM_FW_IMAGES; i++) अणु
		release_firmware(qla1280_fw_tbl[i].fw);
		qla1280_fw_tbl[i].fw = शून्य;
	पूर्ण
पूर्ण

module_init(qla1280_init);
module_निकास(qla1280_निकास);

MODULE_AUTHOR("Qlogic & Jes Sorensen");
MODULE_DESCRIPTION("Qlogic ISP SCSI (qla1x80/qla1x160) driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("qlogic/1040.bin");
MODULE_FIRMWARE("qlogic/1280.bin");
MODULE_FIRMWARE("qlogic/12160.bin");
MODULE_VERSION(QLA1280_VERSION);
