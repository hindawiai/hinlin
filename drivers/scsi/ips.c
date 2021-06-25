<शैली गुरु>
/*****************************************************************************/
/* ips.c -- driver क्रम the Adaptec / IBM ServeRAID controller                */
/*                                                                           */
/* Written By: Keith Mitchell, IBM Corporation                               */
/*             Jack Hammer, Adaptec, Inc.                                    */
/*             David Jeffery, Adaptec, Inc.                                  */
/*                                                                           */
/* Copyright (C) 2000 IBM Corporation                                        */
/* Copyright (C) 2002,2003 Adaptec, Inc.                                     */
/*                                                                           */
/* This program is मुक्त software; you can redistribute it and/or modअगरy      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License क्रम more details.                              */
/*                                                                           */
/* NO WARRANTY                                                               */
/* THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR        */
/* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT      */
/* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,      */
/* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is    */
/* solely responsible क्रम determining the appropriateness of using and       */
/* distributing the Program and assumes all risks associated with its        */
/* exercise of rights under this Agreement, including but not limited to     */
/* the risks and costs of program errors, damage to or loss of data,         */
/* programs or equipment, and unavailability or पूर्णांकerruption of operations.  */
/*                                                                           */
/* DISCLAIMER OF LIABILITY                                                   */
/* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY   */
/* सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        */
/* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND   */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     */
/* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE    */
/* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED  */
/* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES             */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* aदीर्घ with this program; अगर not, ग_लिखो to the Free Software               */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/* Bugs/Comments/Suggestions about this driver should be mailed to:          */
/*      ipslinux@adaptec.com        	                                     */
/*                                                                           */
/* For प्रणाली support issues, contact your local IBM Customer support.       */
/* Directions to find IBM Customer Support क्रम each country can be found at: */
/*      http://www.ibm.com/planetwide/                                       */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Change Log                                                                */
/*                                                                           */
/* 0.99.02  - Breakup commands that are bigger than 8 * the stripe size      */
/* 0.99.03  - Make पूर्णांकerrupt routine handle all completed request on the     */
/*            adapter not just the first one                                 */
/*          - Make sure passthru commands get woken up अगर we run out of      */
/*            SCBs                                                           */
/*          - Send all of the commands on the queue at once rather than      */
/*            one at a समय since the card will support it.                  */
/* 0.99.04  - Fix race condition in the passthru mechanism -- this required  */
/*            the पूर्णांकerface to the utilities to change                       */
/*          - Fix error recovery code                                        */
/* 0.99.05  - Fix an oops when we get certain passthru commands              */
/* 1.00.00  - Initial Public Release                                         */
/*            Functionally equivalent to 0.99.05                             */
/* 3.60.00  - Bump max commands to 128 क्रम use with firmware 3.60            */
/*          - Change version to 3.60 to coincide with release numbering.     */
/* 3.60.01  - Remove bogus error check in passthru routine                   */
/* 3.60.02  - Make DCDB direction based on lookup table                      */
/*          - Only allow one DCDB command to a SCSI ID at a समय             */
/* 4.00.00  - Add support क्रम ServeRAID 4                                    */
/* 4.00.01  - Add support क्रम First Failure Data Capture                     */
/* 4.00.02  - Fix problem with PT DCDB with no buffer                        */
/* 4.00.03  - Add alternative passthru पूर्णांकerface                             */
/*          - Add ability to flash BIOS                                      */
/* 4.00.04  - Rename काष्ठाures/स्थिरants to be prefixed with IPS_           */
/* 4.00.05  - Remove wish_block from init routine                            */
/*          - Use linux/spinlock.h instead of यंत्र/spinlock.h क्रम kernels     */
/*            2.3.18 and later                                               */
/*          - Sync with other changes from the 2.3 kernels                   */
/* 4.00.06  - Fix समयout with initial FFDC command                          */
/* 4.00.06a - Port to 2.4 (trivial) -- Christoph Hellwig <hch@infradead.org> */
/* 4.10.00  - Add support क्रम ServeRAID 4M/4L                                */
/* 4.10.13  - Fix क्रम dynamic unload and proc file प्रणाली                    */
/* 4.20.03  - Rename version to coincide with new release schedules          */
/*            Perक्रमmance fixes                                              */
/*            Fix truncation of /proc files with cat                         */
/*            Merge in changes through kernel 2.4.0test1ac21                 */
/* 4.20.13  - Fix some failure हालs / reset code                            */
/*          - Hook पूर्णांकo the reboot_notअगरier to flush the controller cache    */
/* 4.50.01  - Fix problem when there is a hole in logical drive numbering    */
/* 4.70.09  - Use a Common ( Large Buffer ) क्रम Flashing from the JCRM CD    */
/*          - Add IPSSEND Flash Support                                      */
/*          - Set Sense Data क्रम Unknown SCSI Command                        */
/*          - Use Slot Number from NVRAM Page 5                              */
/*          - Restore caller's DCDB Structure                                */
/* 4.70.12  - Corrective actions क्रम bad controller ( during initialization )*/
/* 4.70.13  - Don't Send CDB's अगर we alपढ़ोy know the device is not present  */
/*          - Don't release HA Lock in ips_next() until SC taken off queue   */
/*          - Unरेजिस्टर SCSI device in ips_release()                        */
/* 4.70.15  - Fix Breakup क्रम very large ( non-SG ) requests in ips_करोne()   */
/* 4.71.00  - Change all memory allocations to not use GFP_DMA flag          */
/*            Code Clean-Up क्रम 2.4.x kernel                                 */
/* 4.72.00  - Allow क्रम a Scatter-Gather Element to exceed MAX_XFER Size     */
/* 4.72.01  - I/O Mapped Memory release ( so "insmod ips" करोes not Fail )    */
/*          - Don't Issue Internal FFDC Command अगर there are Active Commands */
/*          - Close Winकरोw क्रम getting too many IOCTL's active               */
/* 4.80.00  - Make ia64 Safe                                                 */
/* 4.80.04  - Eliminate calls to म_मोहर() अगर 2.4.x or greater                */
/*          - Adjusपंचांगents to Device Queue Depth                              */
/* 4.80.14  - Take all semaphores off stack                                  */
/*          - Clean Up New_IOCTL path                                        */
/* 4.80.20  - Set max_sectors in Scsi_Host काष्ठाure ( अगर >= 2.4.7 kernel )  */
/*          - 5 second delay needed after resetting an i960 adapter          */
/* 4.80.26  - Clean up potential code problems ( Arjan's recommendations )   */
/* 4.90.01  - Version Matching क्रम FirmWare, BIOS, and Driver                */
/* 4.90.05  - Use New PCI Architecture to facilitate Hot Plug Development    */
/* 4.90.08  - Increase Delays in Flashing ( Trombone Only - 4H )             */
/* 4.90.08  - Data Corruption अगर First Scatter Gather Element is > 64K       */
/* 4.90.11  - Don't actually RESET unless it's physically required           */
/*          - Remove unused compile options                                  */
/* 5.00.01  - Sarasota ( 5i ) adapters must always be scanned first          */
/*          - Get rid on IOCTL_NEW_COMMAND code                              */
/*          - Add Extended DCDB Commands क्रम Tape Support in 5I              */
/* 5.10.12  - use pci_dma पूर्णांकerfaces, update क्रम 2.5 kernel changes          */
/* 5.10.15  - हटाओ unused code (sem, macros, etc.)                         */
/* 5.30.00  - use __devनिकास_p()                                              */
/* 6.00.00  - Add 6x Adapters and Battery Flash                              */
/* 6.10.00  - Remove 1G Addressing Limitations                               */
/* 6.11.xx  - Get VersionInfo buffer off the stack !              DDTS 60401 */
/* 6.11.xx  - Make Logical Drive Info काष्ठाure safe क्रम DMA      DDTS 60639 */
/* 7.10.18  - Add highmem_io flag in SCSI Templete क्रम 2.4 kernels           */
/*          - Fix path/name क्रम scsi_hosts.h include क्रम 2.6 kernels         */
/*          - Fix sort order of 7k                                           */
/*          - Remove 3 unused "inline" functions                             */
/* 7.12.xx  - Use STATIC functions wherever possible                        */
/*          - Clean up deprecated MODULE_PARM calls                          */
/* 7.12.05  - Remove Version Matching per IBM request                        */
/*****************************************************************************/

/*
 * Conditional Compilation directives क्रम this driver:
 *
 * IPS_DEBUG            - Turn on debugging info
 *
 * Parameters:
 *
 * debug:<number>       - Set debug level to <number>
 *                        NOTE: only works when IPS_DEBUG compile directive is used.
 *       1              - Normal debug messages
 *       2              - Verbose debug messages
 *       11             - Method trace (non पूर्णांकerrupt)
 *       12             - Method trace (includes पूर्णांकerrupt)
 *
 * noi2o                - Don't use I2O Queues (ServeRAID 4 only)
 * nommap               - Don't use memory mapped I/O
 * ioctlsize            - Initial size of the IOCTL buffer
 */

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/blkdev.h>
#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>

#समावेश <scsi/sg.h>
#समावेश "scsi.h"
#समावेश <scsi/scsi_host.h>

#समावेश "ips.h"

#समावेश <linux/module.h>

#समावेश <linux/स्थिति.स>

#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>

#समावेश <linux/smp.h>

#अगर_घोषित MODULE
अटल अक्षर *ips = शून्य;
module_param(ips, अक्षरp, 0);
#पूर्ण_अगर

/*
 * DRIVER_VER
 */
#घोषणा IPS_VERSION_HIGH        IPS_VER_MAJOR_STRING "." IPS_VER_MINOR_STRING
#घोषणा IPS_VERSION_LOW         "." IPS_VER_BUILD_STRING " "

#घोषणा IPS_DMA_सूची(scb) ((!scb->scsi_cmd || ips_is_passthru(scb->scsi_cmd) || \
                         DMA_NONE == scb->scsi_cmd->sc_data_direction) ? \
                         DMA_BIसूचीECTIONAL : \
                         scb->scsi_cmd->sc_data_direction)

#अगर_घोषित IPS_DEBUG
#घोषणा METHOD_TRACE(s, i)    अगर (ips_debug >= (i+10)) prपूर्णांकk(KERN_NOTICE s "\n");
#घोषणा DEBUG(i, s)           अगर (ips_debug >= i) prपूर्णांकk(KERN_NOTICE s "\n");
#घोषणा DEBUG_VAR(i, s, v...) अगर (ips_debug >= i) prपूर्णांकk(KERN_NOTICE s "\n", v);
#अन्यथा
#घोषणा METHOD_TRACE(s, i)
#घोषणा DEBUG(i, s)
#घोषणा DEBUG_VAR(i, s, v...)
#पूर्ण_अगर

/*
 * Function prototypes
 */
अटल पूर्णांक ips_eh_पात(काष्ठा scsi_cmnd *);
अटल पूर्णांक ips_eh_reset(काष्ठा scsi_cmnd *);
अटल पूर्णांक ips_queue(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
अटल स्थिर अक्षर *ips_info(काष्ठा Scsi_Host *);
अटल irqवापस_t करो_ipsपूर्णांकr(पूर्णांक, व्योम *);
अटल पूर्णांक ips_hainit(ips_ha_t *);
अटल पूर्णांक ips_map_status(ips_ha_t *, ips_scb_t *, ips_stat_t *);
अटल पूर्णांक ips_send_रुको(ips_ha_t *, ips_scb_t *, पूर्णांक, पूर्णांक);
अटल पूर्णांक ips_send_cmd(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_online(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_inquiry(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_rdcap(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_msense(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_reqsen(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_deallocatescbs(ips_ha_t *, पूर्णांक);
अटल पूर्णांक ips_allocatescbs(ips_ha_t *);
अटल पूर्णांक ips_reset_copperhead(ips_ha_t *);
अटल पूर्णांक ips_reset_copperhead_memio(ips_ha_t *);
अटल पूर्णांक ips_reset_morpheus(ips_ha_t *);
अटल पूर्णांक ips_issue_copperhead(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_issue_copperhead_memio(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_issue_i2o(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_issue_i2o_memio(ips_ha_t *, ips_scb_t *);
अटल पूर्णांक ips_isपूर्णांकr_copperhead(ips_ha_t *);
अटल पूर्णांक ips_isपूर्णांकr_copperhead_memio(ips_ha_t *);
अटल पूर्णांक ips_isपूर्णांकr_morpheus(ips_ha_t *);
अटल पूर्णांक ips_रुको(ips_ha_t *, पूर्णांक, पूर्णांक);
अटल पूर्णांक ips_ग_लिखो_driver_status(ips_ha_t *, पूर्णांक);
अटल पूर्णांक ips_पढ़ो_adapter_status(ips_ha_t *, पूर्णांक);
अटल पूर्णांक ips_पढ़ो_subप्रणाली_parameters(ips_ha_t *, पूर्णांक);
अटल पूर्णांक ips_पढ़ो_config(ips_ha_t *, पूर्णांक);
अटल पूर्णांक ips_clear_adapter(ips_ha_t *, पूर्णांक);
अटल पूर्णांक ips_पढ़ोग_लिखो_page5(ips_ha_t *, पूर्णांक, पूर्णांक);
अटल पूर्णांक ips_init_copperhead(ips_ha_t *);
अटल पूर्णांक ips_init_copperhead_memio(ips_ha_t *);
अटल पूर्णांक ips_init_morpheus(ips_ha_t *);
अटल पूर्णांक ips_isinit_copperhead(ips_ha_t *);
अटल पूर्णांक ips_isinit_copperhead_memio(ips_ha_t *);
अटल पूर्णांक ips_isinit_morpheus(ips_ha_t *);
अटल पूर्णांक ips_erase_bios(ips_ha_t *);
अटल पूर्णांक ips_program_bios(ips_ha_t *, अक्षर *, uपूर्णांक32_t, uपूर्णांक32_t);
अटल पूर्णांक ips_verअगरy_bios(ips_ha_t *, अक्षर *, uपूर्णांक32_t, uपूर्णांक32_t);
अटल पूर्णांक ips_erase_bios_memio(ips_ha_t *);
अटल पूर्णांक ips_program_bios_memio(ips_ha_t *, अक्षर *, uपूर्णांक32_t, uपूर्णांक32_t);
अटल पूर्णांक ips_verअगरy_bios_memio(ips_ha_t *, अक्षर *, uपूर्णांक32_t, uपूर्णांक32_t);
अटल पूर्णांक ips_flash_copperhead(ips_ha_t *, ips_passthru_t *, ips_scb_t *);
अटल पूर्णांक ips_flash_bios(ips_ha_t *, ips_passthru_t *, ips_scb_t *);
अटल पूर्णांक ips_flash_firmware(ips_ha_t *, ips_passthru_t *, ips_scb_t *);
अटल व्योम ips_मुक्त_flash_copperhead(ips_ha_t * ha);
अटल व्योम ips_get_bios_version(ips_ha_t *, पूर्णांक);
अटल व्योम ips_identअगरy_controller(ips_ha_t *);
अटल व्योम ips_chkstatus(ips_ha_t *, IPS_STATUS *);
अटल व्योम ips_enable_पूर्णांक_copperhead(ips_ha_t *);
अटल व्योम ips_enable_पूर्णांक_copperhead_memio(ips_ha_t *);
अटल व्योम ips_enable_पूर्णांक_morpheus(ips_ha_t *);
अटल पूर्णांक ips_पूर्णांकr_copperhead(ips_ha_t *);
अटल पूर्णांक ips_पूर्णांकr_morpheus(ips_ha_t *);
अटल व्योम ips_next(ips_ha_t *, पूर्णांक);
अटल व्योम ipsपूर्णांकr_blocking(ips_ha_t *, काष्ठा ips_scb *);
अटल व्योम ipsपूर्णांकr_करोne(ips_ha_t *, काष्ठा ips_scb *);
अटल व्योम ips_करोne(ips_ha_t *, ips_scb_t *);
अटल व्योम ips_मुक्त(ips_ha_t *);
अटल व्योम ips_init_scb(ips_ha_t *, ips_scb_t *);
अटल व्योम ips_मुक्तscb(ips_ha_t *, ips_scb_t *);
अटल व्योम ips_setup_funclist(ips_ha_t *);
अटल व्योम ips_statinit(ips_ha_t *);
अटल व्योम ips_statinit_memio(ips_ha_t *);
अटल व्योम ips_fix_ffdc_समय(ips_ha_t *, ips_scb_t *, समय64_t);
अटल व्योम ips_ffdc_reset(ips_ha_t *, पूर्णांक);
अटल व्योम ips_ffdc_समय(ips_ha_t *);
अटल uपूर्णांक32_t ips_statupd_copperhead(ips_ha_t *);
अटल uपूर्णांक32_t ips_statupd_copperhead_memio(ips_ha_t *);
अटल uपूर्णांक32_t ips_statupd_morpheus(ips_ha_t *);
अटल ips_scb_t *ips_माला_लोcb(ips_ha_t *);
अटल व्योम ips_putq_scb_head(ips_scb_queue_t *, ips_scb_t *);
अटल व्योम ips_putq_रुको_tail(ips_रुको_queue_entry_t *, काष्ठा scsi_cmnd *);
अटल व्योम ips_putq_copp_tail(ips_copp_queue_t *,
				      ips_copp_रुको_item_t *);
अटल ips_scb_t *ips_हटाओq_scb_head(ips_scb_queue_t *);
अटल ips_scb_t *ips_हटाओq_scb(ips_scb_queue_t *, ips_scb_t *);
अटल काष्ठा scsi_cmnd *ips_हटाओq_रुको_head(ips_रुको_queue_entry_t *);
अटल काष्ठा scsi_cmnd *ips_हटाओq_रुको(ips_रुको_queue_entry_t *,
					  काष्ठा scsi_cmnd *);
अटल ips_copp_रुको_item_t *ips_हटाओq_copp(ips_copp_queue_t *,
						     ips_copp_रुको_item_t *);
अटल ips_copp_रुको_item_t *ips_हटाओq_copp_head(ips_copp_queue_t *);

अटल पूर्णांक ips_is_passthru(काष्ठा scsi_cmnd *);
अटल पूर्णांक ips_make_passthru(ips_ha_t *, काष्ठा scsi_cmnd *, ips_scb_t *, पूर्णांक);
अटल पूर्णांक ips_usrcmd(ips_ha_t *, ips_passthru_t *, ips_scb_t *);
अटल व्योम ips_cleanup_passthru(ips_ha_t *, ips_scb_t *);
अटल व्योम ips_scmd_buf_ग_लिखो(काष्ठा scsi_cmnd * scmd, व्योम *data,
			       अचिन्हित पूर्णांक count);
अटल व्योम ips_scmd_buf_पढ़ो(काष्ठा scsi_cmnd * scmd, व्योम *data,
			      अचिन्हित पूर्णांक count);

अटल पूर्णांक ips_ग_लिखो_info(काष्ठा Scsi_Host *, अक्षर *, पूर्णांक);
अटल पूर्णांक ips_show_info(काष्ठा seq_file *, काष्ठा Scsi_Host *);
अटल पूर्णांक ips_host_info(ips_ha_t *, काष्ठा seq_file *);
अटल पूर्णांक ips_पात_init(ips_ha_t * ha, पूर्णांक index);
अटल पूर्णांक ips_init_phase2(पूर्णांक index);

अटल पूर्णांक ips_init_phase1(काष्ठा pci_dev *pci_dev, पूर्णांक *indexPtr);
अटल पूर्णांक ips_रेजिस्टर_scsi(पूर्णांक index);

अटल पूर्णांक  ips_poll_क्रम_flush_complete(ips_ha_t * ha);
अटल व्योम ips_flush_and_reset(ips_ha_t *ha);

/*
 * global variables
 */
अटल स्थिर अक्षर ips_name[] = "ips";
अटल काष्ठा Scsi_Host *ips_sh[IPS_MAX_ADAPTERS];	/* Array of host controller काष्ठाures */
अटल ips_ha_t *ips_ha[IPS_MAX_ADAPTERS];	/* Array of HA काष्ठाures */
अटल अचिन्हित पूर्णांक ips_next_controller;
अटल अचिन्हित पूर्णांक ips_num_controllers;
अटल अचिन्हित पूर्णांक ips_released_controllers;
अटल पूर्णांक ips_hotplug;
अटल पूर्णांक ips_cmd_समयout = 60;
अटल पूर्णांक ips_reset_समयout = 60 * 5;
अटल पूर्णांक ips_क्रमce_memio = 1;		/* Always use Memory Mapped I/O    */
अटल पूर्णांक ips_क्रमce_i2o = 1;	/* Always use I2O command delivery */
अटल पूर्णांक ips_ioctlsize = IPS_IOCTL_SIZE;	/* Size of the ioctl buffer        */
अटल पूर्णांक ips_cd_boot;			/* Booting from Manager CD         */
अटल अक्षर *ips_FlashData = शून्य;	/* CD Boot - Flash Data Buffer      */
अटल dma_addr_t ips_flashbusaddr;
अटल दीर्घ ips_FlashDataInUse;		/* CD Boot - Flash Data In Use Flag */
अटल uपूर्णांक32_t MaxLiteCmds = 32;	/* Max Active Cmds क्रम a Lite Adapter */
अटल काष्ठा scsi_host_ढाँचा ips_driver_ढाँचा = अणु
	.info			= ips_info,
	.queuecommand		= ips_queue,
	.eh_पात_handler	= ips_eh_पात,
	.eh_host_reset_handler	= ips_eh_reset,
	.proc_name		= "ips",
	.show_info		= ips_show_info,
	.ग_लिखो_info		= ips_ग_लिखो_info,
	.slave_configure	= ips_slave_configure,
	.bios_param		= ips_biosparam,
	.this_id		= -1,
	.sg_tablesize		= IPS_MAX_SG,
	.cmd_per_lun		= 3,
	.no_ग_लिखो_same		= 1,
पूर्ण;


/* This table describes all ServeRAID Adapters */
अटल काष्ठा  pci_device_id  ips_pci_table[] = अणु
	अणु 0x1014, 0x002E, PCI_ANY_ID, PCI_ANY_ID, 0, 0 पूर्ण,
	अणु 0x1014, 0x01BD, PCI_ANY_ID, PCI_ANY_ID, 0, 0 पूर्ण,
	अणु 0x9005, 0x0250, PCI_ANY_ID, PCI_ANY_ID, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE( pci, ips_pci_table );

अटल अक्षर ips_hot_plug_name[] = "ips";

अटल पूर्णांक  ips_insert_device(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम ips_हटाओ_device(काष्ठा pci_dev *pci_dev);

अटल काष्ठा pci_driver ips_pci_driver = अणु
	.name		= ips_hot_plug_name,
	.id_table	= ips_pci_table,
	.probe		= ips_insert_device,
	.हटाओ		= ips_हटाओ_device,
पूर्ण;


/*
 * Necessary क्रमward function protoypes
 */
अटल पूर्णांक ips_halt(काष्ठा notअगरier_block *nb, uदीर्घ event, व्योम *buf);

#घोषणा MAX_ADAPTER_NAME 15

अटल अक्षर ips_adapter_name[][30] = अणु
	"ServeRAID",
	"ServeRAID II",
	"ServeRAID on motherboard",
	"ServeRAID on motherboard",
	"ServeRAID 3H",
	"ServeRAID 3L",
	"ServeRAID 4H",
	"ServeRAID 4M",
	"ServeRAID 4L",
	"ServeRAID 4Mx",
	"ServeRAID 4Lx",
	"ServeRAID 5i",
	"ServeRAID 5i",
	"ServeRAID 6M",
	"ServeRAID 6i",
	"ServeRAID 7t",
	"ServeRAID 7k",
	"ServeRAID 7M"
पूर्ण;

अटल काष्ठा notअगरier_block ips_notअगरier = अणु
	ips_halt, शून्य, 0
पूर्ण;

/*
 * Direction table
 */
अटल अक्षर ips_command_direction[] = अणु
	IPS_DATA_NONE, IPS_DATA_NONE, IPS_DATA_IN, IPS_DATA_IN, IPS_DATA_OUT,
	IPS_DATA_IN, IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_IN, IPS_DATA_UNK,
	IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_IN, IPS_DATA_NONE, IPS_DATA_NONE, IPS_DATA_IN, IPS_DATA_OUT,
	IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_NONE, IPS_DATA_NONE, IPS_DATA_OUT,
	IPS_DATA_NONE, IPS_DATA_IN, IPS_DATA_NONE, IPS_DATA_IN, IPS_DATA_OUT,
	IPS_DATA_NONE, IPS_DATA_UNK, IPS_DATA_IN, IPS_DATA_UNK, IPS_DATA_IN,
	IPS_DATA_UNK, IPS_DATA_OUT, IPS_DATA_IN, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_IN, IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_NONE, IPS_DATA_UNK,
	IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_OUT,
	IPS_DATA_OUT, IPS_DATA_NONE, IPS_DATA_IN, IPS_DATA_NONE, IPS_DATA_NONE,
	IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_OUT,
	IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_OUT,
	IPS_DATA_OUT, IPS_DATA_IN, IPS_DATA_IN, IPS_DATA_IN, IPS_DATA_NONE,
	IPS_DATA_UNK, IPS_DATA_NONE, IPS_DATA_NONE, IPS_DATA_NONE, IPS_DATA_UNK,
	IPS_DATA_NONE, IPS_DATA_OUT, IPS_DATA_IN, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_OUT, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_IN, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_NONE, IPS_DATA_NONE, IPS_DATA_UNK, IPS_DATA_IN, IPS_DATA_NONE,
	IPS_DATA_OUT, IPS_DATA_UNK, IPS_DATA_NONE, IPS_DATA_UNK, IPS_DATA_OUT,
	IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_OUT, IPS_DATA_NONE,
	IPS_DATA_UNK, IPS_DATA_IN, IPS_DATA_OUT, IPS_DATA_IN, IPS_DATA_IN,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_OUT,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK,
	IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK, IPS_DATA_UNK
पूर्ण;


/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_setup                                                  */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   setup parameters to the driver                                         */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_setup(अक्षर *ips_str)
अणु

	पूर्णांक i;
	अक्षर *key;
	अक्षर *value;
	अटल स्थिर IPS_OPTION options[] = अणु
		अणु"noi2o", &ips_क्रमce_i2o, 0पूर्ण,
		अणु"nommap", &ips_क्रमce_memio, 0पूर्ण,
		अणु"ioctlsize", &ips_ioctlsize, IPS_IOCTL_SIZEपूर्ण,
		अणु"cdboot", &ips_cd_boot, 0पूर्ण,
		अणु"maxcmds", &MaxLiteCmds, 32पूर्ण,
	पूर्ण;

	/* Don't use म_मोहर() anymore ( अगर 2.4 Kernel or beyond ) */
	/* Search क्रम value */
	जबतक ((key = strsep(&ips_str, ",."))) अणु
		अगर (!*key)
			जारी;
		value = म_अक्षर(key, ':');
		अगर (value)
			*value++ = '\0';
		/*
		 * We now have key/value pairs.
		 * Update the variables
		 */
		क्रम (i = 0; i < ARRAY_SIZE(options); i++) अणु
			अगर (strnहालcmp
			    (key, options[i].option_name,
			     म_माप(options[i].option_name)) == 0) अणु
				अगर (value)
					*options[i].option_flag =
					    simple_म_से_अदीर्घ(value, शून्य, 0);
				अन्यथा
					*options[i].option_flag =
					    options[i].option_value;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस (1);
पूर्ण

__setup("ips=", ips_setup);

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_detect                                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Detect and initialize the driver                                       */
/*                                                                          */
/* NOTE: this routine is called under the io_request_lock spinlock          */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_detect(काष्ठा scsi_host_ढाँचा * SHT)
अणु
	पूर्णांक i;

	METHOD_TRACE("ips_detect", 1);

#अगर_घोषित MODULE
	अगर (ips)
		ips_setup(ips);
#पूर्ण_अगर

	क्रम (i = 0; i < ips_num_controllers; i++) अणु
		अगर (ips_रेजिस्टर_scsi(i))
			ips_मुक्त(ips_ha[i]);
		ips_released_controllers++;
	पूर्ण
	ips_hotplug = 1;
	वापस (ips_num_controllers);
पूर्ण

/****************************************************************************/
/*   configure the function poपूर्णांकers to use the functions that will work    */
/*   with the found version of the adapter                                  */
/****************************************************************************/
अटल व्योम
ips_setup_funclist(ips_ha_t * ha)
अणु

	/*
	 * Setup Functions
	 */
	अगर (IPS_IS_MORPHEUS(ha) || IPS_IS_MARCO(ha)) अणु
		/* morpheus / marco / sebring */
		ha->func.isपूर्णांकr = ips_isपूर्णांकr_morpheus;
		ha->func.isinit = ips_isinit_morpheus;
		ha->func.issue = ips_issue_i2o_memio;
		ha->func.init = ips_init_morpheus;
		ha->func.statupd = ips_statupd_morpheus;
		ha->func.reset = ips_reset_morpheus;
		ha->func.पूर्णांकr = ips_पूर्णांकr_morpheus;
		ha->func.enableपूर्णांक = ips_enable_पूर्णांक_morpheus;
	पूर्ण अन्यथा अगर (IPS_USE_MEMIO(ha)) अणु
		/* copperhead w/MEMIO */
		ha->func.isपूर्णांकr = ips_isपूर्णांकr_copperhead_memio;
		ha->func.isinit = ips_isinit_copperhead_memio;
		ha->func.init = ips_init_copperhead_memio;
		ha->func.statupd = ips_statupd_copperhead_memio;
		ha->func.statinit = ips_statinit_memio;
		ha->func.reset = ips_reset_copperhead_memio;
		ha->func.पूर्णांकr = ips_पूर्णांकr_copperhead;
		ha->func.erasebios = ips_erase_bios_memio;
		ha->func.programbios = ips_program_bios_memio;
		ha->func.verअगरybios = ips_verअगरy_bios_memio;
		ha->func.enableपूर्णांक = ips_enable_पूर्णांक_copperhead_memio;
		अगर (IPS_USE_I2O_DELIVER(ha))
			ha->func.issue = ips_issue_i2o_memio;
		अन्यथा
			ha->func.issue = ips_issue_copperhead_memio;
	पूर्ण अन्यथा अणु
		/* copperhead */
		ha->func.isपूर्णांकr = ips_isपूर्णांकr_copperhead;
		ha->func.isinit = ips_isinit_copperhead;
		ha->func.init = ips_init_copperhead;
		ha->func.statupd = ips_statupd_copperhead;
		ha->func.statinit = ips_statinit;
		ha->func.reset = ips_reset_copperhead;
		ha->func.पूर्णांकr = ips_पूर्णांकr_copperhead;
		ha->func.erasebios = ips_erase_bios;
		ha->func.programbios = ips_program_bios;
		ha->func.verअगरybios = ips_verअगरy_bios;
		ha->func.enableपूर्णांक = ips_enable_पूर्णांक_copperhead;

		अगर (IPS_USE_I2O_DELIVER(ha))
			ha->func.issue = ips_issue_i2o;
		अन्यथा
			ha->func.issue = ips_issue_copperhead;
	पूर्ण
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_release                                                */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove a driver                                                        */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_release(काष्ठा Scsi_Host *sh)
अणु
	ips_scb_t *scb;
	ips_ha_t *ha;
	पूर्णांक i;

	METHOD_TRACE("ips_release", 1);

	scsi_हटाओ_host(sh);

	क्रम (i = 0; i < IPS_MAX_ADAPTERS && ips_sh[i] != sh; i++) ;

	अगर (i == IPS_MAX_ADAPTERS) अणु
		prपूर्णांकk(KERN_WARNING
		       "(%s) release, invalid Scsi_Host pointer.\n", ips_name);
		BUG();
		वापस (FALSE);
	पूर्ण

	ha = IPS_HA(sh);

	अगर (!ha)
		वापस (FALSE);

	/* flush the cache on the controller */
	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_cmd_समयout;
	scb->cdb[0] = IPS_CMD_FLUSH;

	scb->cmd.flush_cache.op_code = IPS_CMD_FLUSH;
	scb->cmd.flush_cache.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.flush_cache.state = IPS_NORM_STATE;
	scb->cmd.flush_cache.reserved = 0;
	scb->cmd.flush_cache.reserved2 = 0;
	scb->cmd.flush_cache.reserved3 = 0;
	scb->cmd.flush_cache.reserved4 = 0;

	IPS_PRINTK(KERN_WARNING, ha->pcidev, "Flushing Cache.\n");

	/* send command */
	अगर (ips_send_रुको(ha, scb, ips_cmd_समयout, IPS_INTR_ON) == IPS_FAILURE)
		IPS_PRINTK(KERN_WARNING, ha->pcidev, "Incomplete Flush.\n");

	IPS_PRINTK(KERN_WARNING, ha->pcidev, "Flushing Complete.\n");

	ips_sh[i] = शून्य;
	ips_ha[i] = शून्य;

	/* मुक्त extra memory */
	ips_मुक्त(ha);

	/* मुक्त IRQ */
	मुक्त_irq(ha->pcidev->irq, ha);

	scsi_host_put(sh);

	ips_released_controllers++;

	वापस (FALSE);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_halt                                                   */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Perक्रमm cleanup when the प्रणाली reboots                                */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_halt(काष्ठा notअगरier_block *nb, uदीर्घ event, व्योम *buf)
अणु
	ips_scb_t *scb;
	ips_ha_t *ha;
	पूर्णांक i;

	अगर ((event != SYS_RESTART) && (event != SYS_HALT) &&
	    (event != SYS_POWER_OFF))
		वापस (NOTIFY_DONE);

	क्रम (i = 0; i < ips_next_controller; i++) अणु
		ha = (ips_ha_t *) ips_ha[i];

		अगर (!ha)
			जारी;

		अगर (!ha->active)
			जारी;

		/* flush the cache on the controller */
		scb = &ha->scbs[ha->max_cmds - 1];

		ips_init_scb(ha, scb);

		scb->समयout = ips_cmd_समयout;
		scb->cdb[0] = IPS_CMD_FLUSH;

		scb->cmd.flush_cache.op_code = IPS_CMD_FLUSH;
		scb->cmd.flush_cache.command_id = IPS_COMMAND_ID(ha, scb);
		scb->cmd.flush_cache.state = IPS_NORM_STATE;
		scb->cmd.flush_cache.reserved = 0;
		scb->cmd.flush_cache.reserved2 = 0;
		scb->cmd.flush_cache.reserved3 = 0;
		scb->cmd.flush_cache.reserved4 = 0;

		IPS_PRINTK(KERN_WARNING, ha->pcidev, "Flushing Cache.\n");

		/* send command */
		अगर (ips_send_रुको(ha, scb, ips_cmd_समयout, IPS_INTR_ON) ==
		    IPS_FAILURE)
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "Incomplete Flush.\n");
		अन्यथा
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "Flushing Complete.\n");
	पूर्ण

	वापस (NOTIFY_OK);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_eh_पात                                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Abort a command (using the new error code stuff)                       */
/* Note: this routine is called under the io_request_lock                   */
/****************************************************************************/
पूर्णांक ips_eh_पात(काष्ठा scsi_cmnd *SC)
अणु
	ips_ha_t *ha;
	ips_copp_रुको_item_t *item;
	पूर्णांक ret;
	काष्ठा Scsi_Host *host;

	METHOD_TRACE("ips_eh_abort", 1);

	अगर (!SC)
		वापस (FAILED);

	host = SC->device->host;
	ha = (ips_ha_t *) SC->device->host->hostdata;

	अगर (!ha)
		वापस (FAILED);

	अगर (!ha->active)
		वापस (FAILED);

	spin_lock(host->host_lock);

	/* See अगर the command is on the copp queue */
	item = ha->copp_रुकोlist.head;
	जबतक ((item) && (item->scsi_cmd != SC))
		item = item->next;

	अगर (item) अणु
		/* Found it */
		ips_हटाओq_copp(&ha->copp_रुकोlist, item);
		ret = (SUCCESS);

		/* See अगर the command is on the रुको queue */
	पूर्ण अन्यथा अगर (ips_हटाओq_रुको(&ha->scb_रुकोlist, SC)) अणु
		/* command not sent yet */
		ret = (SUCCESS);
	पूर्ण अन्यथा अणु
		/* command must have alपढ़ोy been sent */
		ret = (FAILED);
	पूर्ण

	spin_unlock(host->host_lock);
	वापस ret;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_eh_reset                                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Reset the controller (with new eh error code)                          */
/*                                                                          */
/* NOTE: this routine is called under the io_request_lock spinlock          */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक __ips_eh_reset(काष्ठा scsi_cmnd *SC)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	ips_ha_t *ha;
	ips_scb_t *scb;
	ips_copp_रुको_item_t *item;

	METHOD_TRACE("ips_eh_reset", 1);

#अगर_घोषित NO_IPS_RESET
	वापस (FAILED);
#अन्यथा

	अगर (!SC) अणु
		DEBUG(1, "Reset called with NULL scsi command");

		वापस (FAILED);
	पूर्ण

	ha = (ips_ha_t *) SC->device->host->hostdata;

	अगर (!ha) अणु
		DEBUG(1, "Reset called with NULL ha struct");

		वापस (FAILED);
	पूर्ण

	अगर (!ha->active)
		वापस (FAILED);

	/* See अगर the command is on the copp queue */
	item = ha->copp_रुकोlist.head;
	जबतक ((item) && (item->scsi_cmd != SC))
		item = item->next;

	अगर (item) अणु
		/* Found it */
		ips_हटाओq_copp(&ha->copp_रुकोlist, item);
		वापस (SUCCESS);
	पूर्ण

	/* See अगर the command is on the रुको queue */
	अगर (ips_हटाओq_रुको(&ha->scb_रुकोlist, SC)) अणु
		/* command not sent yet */
		वापस (SUCCESS);
	पूर्ण

	/* An explanation क्रम the casual observer:                              */
	/* Part of the function of a RAID controller is स्वतःmatic error         */
	/* detection and recovery.  As such, the only problem that physically   */
	/* resetting an adapter will ever fix is when, क्रम some reason,         */
	/* the driver is not successfully communicating with the adapter.       */
	/* Thereक्रमe, we will attempt to flush this adapter.  If that succeeds, */
	/* then there's no real purpose in a physical reset. This will complete */
	/* much faster and aव्योमs any problems that might be caused by a        */
	/* physical reset ( such as having to fail all the outstanding I/O's ). */

	अगर (ha->ioctl_reset == 0) अणु	/* IF Not an IOCTL Requested Reset */
		scb = &ha->scbs[ha->max_cmds - 1];

		ips_init_scb(ha, scb);

		scb->समयout = ips_cmd_समयout;
		scb->cdb[0] = IPS_CMD_FLUSH;

		scb->cmd.flush_cache.op_code = IPS_CMD_FLUSH;
		scb->cmd.flush_cache.command_id = IPS_COMMAND_ID(ha, scb);
		scb->cmd.flush_cache.state = IPS_NORM_STATE;
		scb->cmd.flush_cache.reserved = 0;
		scb->cmd.flush_cache.reserved2 = 0;
		scb->cmd.flush_cache.reserved3 = 0;
		scb->cmd.flush_cache.reserved4 = 0;

		/* Attempt the flush command */
		ret = ips_send_रुको(ha, scb, ips_cmd_समयout, IPS_INTR_IORL);
		अगर (ret == IPS_SUCCESS) अणु
			IPS_PRINTK(KERN_NOTICE, ha->pcidev,
				   "Reset Request - Flushed Cache\n");
			वापस (SUCCESS);
		पूर्ण
	पूर्ण

	/* Either we can't communicate with the adapter or it's an IOCTL request */
	/* from a utility.  A physical reset is needed at this poपूर्णांक.            */

	ha->ioctl_reset = 0;	/* Reset the IOCTL Requested Reset Flag */

	/*
	 * command must have alपढ़ोy been sent
	 * reset the controller
	 */
	IPS_PRINTK(KERN_NOTICE, ha->pcidev, "Resetting controller.\n");
	ret = (*ha->func.reset) (ha);

	अगर (!ret) अणु
		काष्ठा scsi_cmnd *scsi_cmd;

		IPS_PRINTK(KERN_NOTICE, ha->pcidev,
			   "Controller reset failed - controller now offline.\n");

		/* Now fail all of the active commands */
		DEBUG_VAR(1, "(%s%d) Failing active commands",
			  ips_name, ha->host_num);

		जबतक ((scb = ips_हटाओq_scb_head(&ha->scb_activelist))) अणु
			scb->scsi_cmd->result = DID_ERROR << 16;
			scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
			ips_मुक्तscb(ha, scb);
		पूर्ण

		/* Now fail all of the pending commands */
		DEBUG_VAR(1, "(%s%d) Failing pending commands",
			  ips_name, ha->host_num);

		जबतक ((scsi_cmd = ips_हटाओq_रुको_head(&ha->scb_रुकोlist))) अणु
			scsi_cmd->result = DID_ERROR;
			scsi_cmd->scsi_करोne(scsi_cmd);
		पूर्ण

		ha->active = FALSE;
		वापस (FAILED);
	पूर्ण

	अगर (!ips_clear_adapter(ha, IPS_INTR_IORL)) अणु
		काष्ठा scsi_cmnd *scsi_cmd;

		IPS_PRINTK(KERN_NOTICE, ha->pcidev,
			   "Controller reset failed - controller now offline.\n");

		/* Now fail all of the active commands */
		DEBUG_VAR(1, "(%s%d) Failing active commands",
			  ips_name, ha->host_num);

		जबतक ((scb = ips_हटाओq_scb_head(&ha->scb_activelist))) अणु
			scb->scsi_cmd->result = DID_ERROR << 16;
			scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
			ips_मुक्तscb(ha, scb);
		पूर्ण

		/* Now fail all of the pending commands */
		DEBUG_VAR(1, "(%s%d) Failing pending commands",
			  ips_name, ha->host_num);

		जबतक ((scsi_cmd = ips_हटाओq_रुको_head(&ha->scb_रुकोlist))) अणु
			scsi_cmd->result = DID_ERROR << 16;
			scsi_cmd->scsi_करोne(scsi_cmd);
		पूर्ण

		ha->active = FALSE;
		वापस (FAILED);
	पूर्ण

	/* FFDC */
	अगर (le32_to_cpu(ha->subsys->param[3]) & 0x300000) अणु
		ha->last_ffdc = kसमय_get_real_seconds();
		ha->reset_count++;
		ips_ffdc_reset(ha, IPS_INTR_IORL);
	पूर्ण

	/* Now fail all of the active commands */
	DEBUG_VAR(1, "(%s%d) Failing active commands", ips_name, ha->host_num);

	जबतक ((scb = ips_हटाओq_scb_head(&ha->scb_activelist))) अणु
		scb->scsi_cmd->result = DID_RESET << 16;
		scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
		ips_मुक्तscb(ha, scb);
	पूर्ण

	/* Reset DCDB active command bits */
	क्रम (i = 1; i < ha->nbus; i++)
		ha->dcdb_active[i - 1] = 0;

	/* Reset the number of active IOCTLs */
	ha->num_ioctl = 0;

	ips_next(ha, IPS_INTR_IORL);

	वापस (SUCCESS);
#पूर्ण_अगर				/* NO_IPS_RESET */

पूर्ण

अटल पूर्णांक ips_eh_reset(काष्ठा scsi_cmnd *SC)
अणु
	पूर्णांक rc;

	spin_lock_irq(SC->device->host->host_lock);
	rc = __ips_eh_reset(SC);
	spin_unlock_irq(SC->device->host->host_lock);

	वापस rc;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_queue                                                  */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Send a command to the controller                                       */
/*                                                                          */
/* NOTE:                                                                    */
/*    Linux obtains io_request_lock beक्रमe calling this function            */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक ips_queue_lck(काष्ठा scsi_cmnd *SC, व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	ips_ha_t *ha;
	ips_passthru_t *pt;

	METHOD_TRACE("ips_queue", 1);

	ha = (ips_ha_t *) SC->device->host->hostdata;

	अगर (!ha)
		जाओ out_error;

	अगर (!ha->active)
		जाओ out_error;

	अगर (ips_is_passthru(SC)) अणु
		अगर (ha->copp_रुकोlist.count == IPS_MAX_IOCTL_QUEUE) अणु
			SC->result = DID_BUS_BUSY << 16;
			करोne(SC);

			वापस (0);
		पूर्ण
	पूर्ण अन्यथा अगर (ha->scb_रुकोlist.count == IPS_MAX_QUEUE) अणु
		SC->result = DID_BUS_BUSY << 16;
		करोne(SC);

		वापस (0);
	पूर्ण

	SC->scsi_करोne = करोne;

	DEBUG_VAR(2, "(%s%d): ips_queue: cmd 0x%X (%d %d %d)",
		  ips_name,
		  ha->host_num,
		  SC->cmnd[0],
		  SC->device->channel, SC->device->id, SC->device->lun);

	/* Check क्रम command to initiator IDs */
	अगर ((scmd_channel(SC) > 0)
	    && (scmd_id(SC) == ha->ha_id[scmd_channel(SC)])) अणु
		SC->result = DID_NO_CONNECT << 16;
		करोne(SC);

		वापस (0);
	पूर्ण

	अगर (ips_is_passthru(SC)) अणु

		ips_copp_रुको_item_t *scratch;

		/* A Reset IOCTL is only sent by the boot CD in extreme हालs.           */
		/* There can never be any प्रणाली activity ( network or disk ), but check */
		/* anyway just as a good practice.                                       */
		pt = (ips_passthru_t *) scsi_sglist(SC);
		अगर ((pt->CoppCP.cmd.reset.op_code == IPS_CMD_RESET_CHANNEL) &&
		    (pt->CoppCP.cmd.reset.adapter_flag == 1)) अणु
			अगर (ha->scb_activelist.count != 0) अणु
				SC->result = DID_BUS_BUSY << 16;
				करोne(SC);
				वापस (0);
			पूर्ण
			ha->ioctl_reset = 1;	/* This reset request is from an IOCTL */
			__ips_eh_reset(SC);
			SC->result = DID_OK << 16;
			SC->scsi_करोne(SC);
			वापस (0);
		पूर्ण

		/* allocate space क्रम the scribble */
		scratch = kदो_स्मृति(माप (ips_copp_रुको_item_t), GFP_ATOMIC);

		अगर (!scratch) अणु
			SC->result = DID_ERROR << 16;
			करोne(SC);

			वापस (0);
		पूर्ण

		scratch->scsi_cmd = SC;
		scratch->next = शून्य;

		ips_putq_copp_tail(&ha->copp_रुकोlist, scratch);
	पूर्ण अन्यथा अणु
		ips_putq_रुको_tail(&ha->scb_रुकोlist, SC);
	पूर्ण

	ips_next(ha, IPS_INTR_IORL);

	वापस (0);
out_error:
	SC->result = DID_ERROR << 16;
	करोne(SC);

	वापस (0);
पूर्ण

अटल DEF_SCSI_QCMD(ips_queue)

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_biosparam                                              */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Set bios geometry क्रम the controller                                   */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक ips_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
			 sector_t capacity, पूर्णांक geom[])
अणु
	ips_ha_t *ha = (ips_ha_t *) sdev->host->hostdata;
	पूर्णांक heads;
	पूर्णांक sectors;
	पूर्णांक cylinders;

	METHOD_TRACE("ips_biosparam", 1);

	अगर (!ha)
		/* ?!?! host adater info invalid */
		वापस (0);

	अगर (!ha->active)
		वापस (0);

	अगर (!ips_पढ़ो_adapter_status(ha, IPS_INTR_ON))
		/* ?!?! Enquiry command failed */
		वापस (0);

	अगर ((capacity > 0x400000) && ((ha->enq->ucMiscFlag & 0x8) == 0)) अणु
		heads = IPS_NORM_HEADS;
		sectors = IPS_NORM_SECTORS;
	पूर्ण अन्यथा अणु
		heads = IPS_COMP_HEADS;
		sectors = IPS_COMP_SECTORS;
	पूर्ण

	cylinders = (अचिन्हित दीर्घ) capacity / (heads * sectors);

	DEBUG_VAR(2, "Geometry: heads: %d, sectors: %d, cylinders: %d",
		  heads, sectors, cylinders);

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_slave_configure                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Set queue depths on devices once scan is complete                      */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_slave_configure(काष्ठा scsi_device * SDptr)
अणु
	ips_ha_t *ha;
	पूर्णांक min;

	ha = IPS_HA(SDptr->host);
	अगर (SDptr->tagged_supported && SDptr->type == TYPE_DISK) अणु
		min = ha->max_cmds / 2;
		अगर (ha->enq->ucLogDriveCount <= 2)
			min = ha->max_cmds - 1;
		scsi_change_queue_depth(SDptr, min);
	पूर्ण

	SDptr->skip_ms_page_8 = 1;
	SDptr->skip_ms_page_3f = 1;
	वापस 0;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: करो_ipsपूर्णांकr                                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Wrapper क्रम the पूर्णांकerrupt handler                                      */
/*                                                                          */
/****************************************************************************/
अटल irqवापस_t
करो_ipsपूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	ips_ha_t *ha;
	काष्ठा Scsi_Host *host;
	पूर्णांक irqstatus;

	METHOD_TRACE("do_ipsintr", 2);

	ha = (ips_ha_t *) dev_id;
	अगर (!ha)
		वापस IRQ_NONE;
	host = ips_sh[ha->host_num];
	/* पूर्णांकerrupt during initialization */
	अगर (!host) अणु
		(*ha->func.पूर्णांकr) (ha);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(host->host_lock);

	अगर (!ha->active) अणु
		spin_unlock(host->host_lock);
		वापस IRQ_HANDLED;
	पूर्ण

	irqstatus = (*ha->func.पूर्णांकr) (ha);

	spin_unlock(host->host_lock);

	/* start the next command */
	ips_next(ha, IPS_INTR_ON);
	वापस IRQ_RETVAL(irqstatus);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_पूर्णांकr_copperhead                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Polling पूर्णांकerrupt handler                                              */
/*                                                                          */
/*   ASSUMES पूर्णांकerrupts are disabled                                        */
/*                                                                          */
/****************************************************************************/
पूर्णांक
ips_पूर्णांकr_copperhead(ips_ha_t * ha)
अणु
	ips_stat_t *sp;
	ips_scb_t *scb;
	IPS_STATUS cstatus;
	पूर्णांक पूर्णांकrstatus;

	METHOD_TRACE("ips_intr", 2);

	अगर (!ha)
		वापस 0;

	अगर (!ha->active)
		वापस 0;

	पूर्णांकrstatus = (*ha->func.isपूर्णांकr) (ha);

	अगर (!पूर्णांकrstatus) अणु
		/*
		 * Unexpected/Shared पूर्णांकerrupt
		 */

		वापस 0;
	पूर्ण

	जबतक (TRUE) अणु
		sp = &ha->sp;

		पूर्णांकrstatus = (*ha->func.isपूर्णांकr) (ha);

		अगर (!पूर्णांकrstatus)
			अवरोध;
		अन्यथा
			cstatus.value = (*ha->func.statupd) (ha);

		अगर (cstatus.fields.command_id > (IPS_MAX_CMDS - 1)) अणु
			/* Spurious Interrupt ? */
			जारी;
		पूर्ण

		ips_chkstatus(ha, &cstatus);
		scb = (ips_scb_t *) sp->scb_addr;

		/*
		 * use the callback function to finish things up
		 * NOTE: पूर्णांकerrupts are OFF क्रम this
		 */
		(*scb->callback) (ha, scb);
	पूर्ण			/* end जबतक */
	वापस 1;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_पूर्णांकr_morpheus                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Polling पूर्णांकerrupt handler                                              */
/*                                                                          */
/*   ASSUMES पूर्णांकerrupts are disabled                                        */
/*                                                                          */
/****************************************************************************/
पूर्णांक
ips_पूर्णांकr_morpheus(ips_ha_t * ha)
अणु
	ips_stat_t *sp;
	ips_scb_t *scb;
	IPS_STATUS cstatus;
	पूर्णांक पूर्णांकrstatus;

	METHOD_TRACE("ips_intr_morpheus", 2);

	अगर (!ha)
		वापस 0;

	अगर (!ha->active)
		वापस 0;

	पूर्णांकrstatus = (*ha->func.isपूर्णांकr) (ha);

	अगर (!पूर्णांकrstatus) अणु
		/*
		 * Unexpected/Shared पूर्णांकerrupt
		 */

		वापस 0;
	पूर्ण

	जबतक (TRUE) अणु
		sp = &ha->sp;

		पूर्णांकrstatus = (*ha->func.isपूर्णांकr) (ha);

		अगर (!पूर्णांकrstatus)
			अवरोध;
		अन्यथा
			cstatus.value = (*ha->func.statupd) (ha);

		अगर (cstatus.value == 0xffffffff)
			/* No more to process */
			अवरोध;

		अगर (cstatus.fields.command_id > (IPS_MAX_CMDS - 1)) अणु
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "Spurious interrupt; no ccb.\n");

			जारी;
		पूर्ण

		ips_chkstatus(ha, &cstatus);
		scb = (ips_scb_t *) sp->scb_addr;

		/*
		 * use the callback function to finish things up
		 * NOTE: पूर्णांकerrupts are OFF क्रम this
		 */
		(*scb->callback) (ha, scb);
	पूर्ण			/* end जबतक */
	वापस 1;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_info                                                   */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Return info about the driver                                           */
/*                                                                          */
/****************************************************************************/
अटल स्थिर अक्षर *
ips_info(काष्ठा Scsi_Host *SH)
अणु
	अटल अक्षर buffer[256];
	अक्षर *bp;
	ips_ha_t *ha;

	METHOD_TRACE("ips_info", 1);

	ha = IPS_HA(SH);

	अगर (!ha)
		वापस (शून्य);

	bp = &buffer[0];
	स_रखो(bp, 0, माप (buffer));

	प्र_लिखो(bp, "%s%s%s Build %d", "IBM PCI ServeRAID ",
		IPS_VERSION_HIGH, IPS_VERSION_LOW, IPS_BUILD_IDENT);

	अगर (ha->ad_type > 0 && ha->ad_type <= MAX_ADAPTER_NAME) अणु
		म_जोड़ो(bp, " <");
		म_जोड़ो(bp, ips_adapter_name[ha->ad_type - 1]);
		म_जोड़ो(bp, ">");
	पूर्ण

	वापस (bp);
पूर्ण

अटल पूर्णांक
ips_ग_लिखो_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
अणु
	पूर्णांक i;
	ips_ha_t *ha = शून्य;

	/* Find our host काष्ठाure */
	क्रम (i = 0; i < ips_next_controller; i++) अणु
		अगर (ips_sh[i]) अणु
			अगर (ips_sh[i] == host) अणु
				ha = (ips_ha_t *) ips_sh[i]->hostdata;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ha)
		वापस (-EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक
ips_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	पूर्णांक i;
	ips_ha_t *ha = शून्य;

	/* Find our host काष्ठाure */
	क्रम (i = 0; i < ips_next_controller; i++) अणु
		अगर (ips_sh[i]) अणु
			अगर (ips_sh[i] == host) अणु
				ha = (ips_ha_t *) ips_sh[i]->hostdata;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ha)
		वापस (-EINVAL);

	वापस ips_host_info(ha, m);
पूर्ण

/*--------------------------------------------------------------------------*/
/* Helper Functions                                                         */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_is_passthru                                            */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Determine अगर the specअगरied SCSI command is really a passthru command   */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक ips_is_passthru(काष्ठा scsi_cmnd *SC)
अणु
	अचिन्हित दीर्घ flags;

	METHOD_TRACE("ips_is_passthru", 1);

	अगर (!SC)
		वापस (0);

	अगर ((SC->cmnd[0] == IPS_IOCTL_COMMAND) &&
	    (SC->device->channel == 0) &&
	    (SC->device->id == IPS_ADAPTER_ID) &&
	    (SC->device->lun == 0) && scsi_sglist(SC)) अणु
                काष्ठा scatterlist *sg = scsi_sglist(SC);
                अक्षर  *buffer;

                /* kmap_atomic() ensures addressability of the user buffer.*/
                /* local_irq_save() protects the KM_IRQ0 address slot.     */
                local_irq_save(flags);
                buffer = kmap_atomic(sg_page(sg)) + sg->offset;
                अगर (buffer && buffer[0] == 'C' && buffer[1] == 'O' &&
                    buffer[2] == 'P' && buffer[3] == 'P') अणु
                        kunmap_atomic(buffer - sg->offset);
                        local_irq_restore(flags);
                        वापस 1;
                पूर्ण
                kunmap_atomic(buffer - sg->offset);
                local_irq_restore(flags);
	पूर्ण
	वापस 0;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_alloc_passthru_buffer                                  */
/*                                                                          */
/* Routine Description:                                                     */
/*   allocate a buffer large enough क्रम the ioctl data अगर the ioctl buffer  */
/*   is too small or करोesn't exist                                          */
/****************************************************************************/
अटल पूर्णांक
ips_alloc_passthru_buffer(ips_ha_t * ha, पूर्णांक length)
अणु
	व्योम *bigger_buf;
	dma_addr_t dma_busaddr;

	अगर (ha->ioctl_data && length <= ha->ioctl_len)
		वापस 0;
	/* there is no buffer or it's not big enough, allocate a new one */
	bigger_buf = dma_alloc_coherent(&ha->pcidev->dev, length, &dma_busaddr,
			GFP_KERNEL);
	अगर (bigger_buf) अणु
		/* मुक्त the old memory */
		dma_मुक्त_coherent(&ha->pcidev->dev, ha->ioctl_len,
				  ha->ioctl_data, ha->ioctl_busaddr);
		/* use the new memory */
		ha->ioctl_data = (अक्षर *) bigger_buf;
		ha->ioctl_len = length;
		ha->ioctl_busaddr = dma_busaddr;
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_make_passthru                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Make a passthru command out of the info in the Scsi block              */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_make_passthru(ips_ha_t *ha, काष्ठा scsi_cmnd *SC, ips_scb_t *scb, पूर्णांक पूर्णांकr)
अणु
	ips_passthru_t *pt;
	पूर्णांक length = 0;
	पूर्णांक i, ret;
        काष्ठा scatterlist *sg = scsi_sglist(SC);

	METHOD_TRACE("ips_make_passthru", 1);

        scsi_क्रम_each_sg(SC, sg, scsi_sg_count(SC), i)
		length += sg->length;

	अगर (length < माप (ips_passthru_t)) अणु
		/* wrong size */
		DEBUG_VAR(1, "(%s%d) Passthru structure wrong size",
			  ips_name, ha->host_num);
		वापस (IPS_FAILURE);
	पूर्ण
	अगर (ips_alloc_passthru_buffer(ha, length)) अणु
		/* allocation failure!  If ha->ioctl_data exists, use it to वापस
		   some error codes.  Return a failed command to the scsi layer. */
		अगर (ha->ioctl_data) अणु
			pt = (ips_passthru_t *) ha->ioctl_data;
			ips_scmd_buf_पढ़ो(SC, pt, माप (ips_passthru_t));
			pt->BasicStatus = 0x0B;
			pt->ExtendedStatus = 0x00;
			ips_scmd_buf_ग_लिखो(SC, pt, माप (ips_passthru_t));
		पूर्ण
		वापस IPS_FAILURE;
	पूर्ण
	ha->ioctl_datasize = length;

	ips_scmd_buf_पढ़ो(SC, ha->ioctl_data, ha->ioctl_datasize);
	pt = (ips_passthru_t *) ha->ioctl_data;

	/*
	 * Some notes about the passthru पूर्णांकerface used
	 *
	 * IF the scsi op_code == 0x0d then we assume
	 * that the data came aदीर्घ with/goes with the
	 * packet we received from the sg driver. In this
	 * हाल the CmdBSize field of the pt काष्ठाure is
	 * used क्रम the size of the buffer.
	 */

	चयन (pt->CoppCmd) अणु
	हाल IPS_NUMCTRLS:
		स_नकल(ha->ioctl_data + माप (ips_passthru_t),
		       &ips_num_controllers, माप (पूर्णांक));
		ips_scmd_buf_ग_लिखो(SC, ha->ioctl_data,
				   माप (ips_passthru_t) + माप (पूर्णांक));
		SC->result = DID_OK << 16;

		वापस (IPS_SUCCESS_IMM);

	हाल IPS_COPPUSRCMD:
	हाल IPS_COPPIOCCMD:
		अगर (SC->cmnd[0] == IPS_IOCTL_COMMAND) अणु
			अगर (length < (माप (ips_passthru_t) + pt->CmdBSize)) अणु
				/* wrong size */
				DEBUG_VAR(1,
					  "(%s%d) Passthru structure wrong size",
					  ips_name, ha->host_num);

				वापस (IPS_FAILURE);
			पूर्ण

			अगर (ha->pcidev->device == IPS_DEVICEID_COPPERHEAD &&
			    pt->CoppCP.cmd.flashfw.op_code ==
			    IPS_CMD_RW_BIOSFW) अणु
				ret = ips_flash_copperhead(ha, pt, scb);
				ips_scmd_buf_ग_लिखो(SC, ha->ioctl_data,
						   माप (ips_passthru_t));
				वापस ret;
			पूर्ण
			अगर (ips_usrcmd(ha, pt, scb))
				वापस (IPS_SUCCESS);
			अन्यथा
				वापस (IPS_FAILURE);
		पूर्ण

		अवरोध;

	पूर्ण			/* end चयन */

	वापस (IPS_FAILURE);
पूर्ण

/****************************************************************************/
/* Routine Name: ips_flash_copperhead                                       */
/* Routine Description:                                                     */
/*   Flash the BIOS/FW on a Copperhead style controller                     */
/****************************************************************************/
अटल पूर्णांक
ips_flash_copperhead(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
अणु
	पूर्णांक datasize;

	/* Trombone is the only copperhead that can करो packet flash, but only
	 * क्रम firmware. No one said it had to make sense. */
	अगर (IPS_IS_TROMBONE(ha) && pt->CoppCP.cmd.flashfw.type == IPS_FW_IMAGE) अणु
		अगर (ips_usrcmd(ha, pt, scb))
			वापस IPS_SUCCESS;
		अन्यथा
			वापस IPS_FAILURE;
	पूर्ण
	pt->BasicStatus = 0x0B;
	pt->ExtendedStatus = 0;
	scb->scsi_cmd->result = DID_OK << 16;
	/* IF it's OK to Use the "CD BOOT" Flash Buffer, then you can     */
	/* aव्योम allocating a huge buffer per adapter ( which can fail ). */
	अगर (pt->CoppCP.cmd.flashfw.type == IPS_BIOS_IMAGE &&
	    pt->CoppCP.cmd.flashfw.direction == IPS_ERASE_BIOS) अणु
		pt->BasicStatus = 0;
		वापस ips_flash_bios(ha, pt, scb);
	पूर्ण अन्यथा अगर (pt->CoppCP.cmd.flashfw.packet_num == 0) अणु
		अगर (ips_FlashData && !test_and_set_bit(0, &ips_FlashDataInUse))अणु
			ha->flash_data = ips_FlashData;
			ha->flash_busaddr = ips_flashbusaddr;
			ha->flash_len = PAGE_SIZE << 7;
			ha->flash_datasize = 0;
		पूर्ण अन्यथा अगर (!ha->flash_data) अणु
			datasize = pt->CoppCP.cmd.flashfw.total_packets *
			    pt->CoppCP.cmd.flashfw.count;
			ha->flash_data = dma_alloc_coherent(&ha->pcidev->dev,
					datasize, &ha->flash_busaddr, GFP_KERNEL);
			अगर (!ha->flash_data)अणु
				prपूर्णांकk(KERN_WARNING "Unable to allocate a flash buffer\n");
				वापस IPS_FAILURE;
			पूर्ण
			ha->flash_datasize = 0;
			ha->flash_len = datasize;
		पूर्ण अन्यथा
			वापस IPS_FAILURE;
	पूर्ण अन्यथा अणु
		अगर (pt->CoppCP.cmd.flashfw.count + ha->flash_datasize >
		    ha->flash_len) अणु
			ips_मुक्त_flash_copperhead(ha);
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "failed size sanity check\n");
			वापस IPS_FAILURE;
		पूर्ण
	पूर्ण
	अगर (!ha->flash_data)
		वापस IPS_FAILURE;
	pt->BasicStatus = 0;
	स_नकल(&ha->flash_data[ha->flash_datasize], pt + 1,
	       pt->CoppCP.cmd.flashfw.count);
	ha->flash_datasize += pt->CoppCP.cmd.flashfw.count;
	अगर (pt->CoppCP.cmd.flashfw.packet_num ==
	    pt->CoppCP.cmd.flashfw.total_packets - 1) अणु
		अगर (pt->CoppCP.cmd.flashfw.type == IPS_BIOS_IMAGE)
			वापस ips_flash_bios(ha, pt, scb);
		अन्यथा अगर (pt->CoppCP.cmd.flashfw.type == IPS_FW_IMAGE)
			वापस ips_flash_firmware(ha, pt, scb);
	पूर्ण
	वापस IPS_SUCCESS_IMM;
पूर्ण

/****************************************************************************/
/* Routine Name: ips_flash_bios                                             */
/* Routine Description:                                                     */
/*   flashes the bios of a copperhead adapter                               */
/****************************************************************************/
अटल पूर्णांक
ips_flash_bios(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
अणु

	अगर (pt->CoppCP.cmd.flashfw.type == IPS_BIOS_IMAGE &&
	    pt->CoppCP.cmd.flashfw.direction == IPS_WRITE_BIOS) अणु
		अगर ((!ha->func.programbios) || (!ha->func.erasebios) ||
		    (!ha->func.verअगरybios))
			जाओ error;
		अगर ((*ha->func.erasebios) (ha)) अणु
			DEBUG_VAR(1,
				  "(%s%d) flash bios failed - unable to erase flash",
				  ips_name, ha->host_num);
			जाओ error;
		पूर्ण अन्यथा
		    अगर ((*ha->func.programbios) (ha,
						 ha->flash_data +
						 IPS_BIOS_HEADER,
						 ha->flash_datasize -
						 IPS_BIOS_HEADER, 0)) अणु
			DEBUG_VAR(1,
				  "(%s%d) flash bios failed - unable to flash",
				  ips_name, ha->host_num);
			जाओ error;
		पूर्ण अन्यथा
		    अगर ((*ha->func.verअगरybios) (ha,
						ha->flash_data +
						IPS_BIOS_HEADER,
						ha->flash_datasize -
						IPS_BIOS_HEADER, 0)) अणु
			DEBUG_VAR(1,
				  "(%s%d) flash bios failed - unable to verify flash",
				  ips_name, ha->host_num);
			जाओ error;
		पूर्ण
		ips_मुक्त_flash_copperhead(ha);
		वापस IPS_SUCCESS_IMM;
	पूर्ण अन्यथा अगर (pt->CoppCP.cmd.flashfw.type == IPS_BIOS_IMAGE &&
		   pt->CoppCP.cmd.flashfw.direction == IPS_ERASE_BIOS) अणु
		अगर (!ha->func.erasebios)
			जाओ error;
		अगर ((*ha->func.erasebios) (ha)) अणु
			DEBUG_VAR(1,
				  "(%s%d) flash bios failed - unable to erase flash",
				  ips_name, ha->host_num);
			जाओ error;
		पूर्ण
		वापस IPS_SUCCESS_IMM;
	पूर्ण
      error:
	pt->BasicStatus = 0x0B;
	pt->ExtendedStatus = 0x00;
	ips_मुक्त_flash_copperhead(ha);
	वापस IPS_FAILURE;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_fill_scb_sg_single                                     */
/*                                                                          */
/* Routine Description:                                                     */
/*   Fill in a single scb sg_list element from an address                   */
/*   वापस a -1 अगर a अवरोधup occurred                                      */
/****************************************************************************/
अटल पूर्णांक
ips_fill_scb_sg_single(ips_ha_t * ha, dma_addr_t busaddr,
		       ips_scb_t * scb, पूर्णांक indx, अचिन्हित पूर्णांक e_len)
अणु

	पूर्णांक ret_val = 0;

	अगर ((scb->data_len + e_len) > ha->max_xfer) अणु
		e_len = ha->max_xfer - scb->data_len;
		scb->अवरोधup = indx;
		++scb->sg_अवरोध;
		ret_val = -1;
	पूर्ण अन्यथा अणु
		scb->अवरोधup = 0;
		scb->sg_अवरोध = 0;
	पूर्ण
	अगर (IPS_USE_ENH_SGLIST(ha)) अणु
		scb->sg_list.enh_list[indx].address_lo =
		    cpu_to_le32(lower_32_bits(busaddr));
		scb->sg_list.enh_list[indx].address_hi =
		    cpu_to_le32(upper_32_bits(busaddr));
		scb->sg_list.enh_list[indx].length = cpu_to_le32(e_len);
	पूर्ण अन्यथा अणु
		scb->sg_list.std_list[indx].address =
		    cpu_to_le32(lower_32_bits(busaddr));
		scb->sg_list.std_list[indx].length = cpu_to_le32(e_len);
	पूर्ण

	++scb->sg_len;
	scb->data_len += e_len;
	वापस ret_val;
पूर्ण

/****************************************************************************/
/* Routine Name: ips_flash_firmware                                         */
/* Routine Description:                                                     */
/*   flashes the firmware of a copperhead adapter                           */
/****************************************************************************/
अटल पूर्णांक
ips_flash_firmware(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
अणु
	IPS_SG_LIST sg_list;
	uपूर्णांक32_t cmd_busaddr;

	अगर (pt->CoppCP.cmd.flashfw.type == IPS_FW_IMAGE &&
	    pt->CoppCP.cmd.flashfw.direction == IPS_WRITE_FW) अणु
		स_रखो(&pt->CoppCP.cmd, 0, माप (IPS_HOST_COMMAND));
		pt->CoppCP.cmd.flashfw.op_code = IPS_CMD_DOWNLOAD;
		pt->CoppCP.cmd.flashfw.count = cpu_to_le32(ha->flash_datasize);
	पूर्ण अन्यथा अणु
		pt->BasicStatus = 0x0B;
		pt->ExtendedStatus = 0x00;
		ips_मुक्त_flash_copperhead(ha);
		वापस IPS_FAILURE;
	पूर्ण
	/* Save the S/G list poपूर्णांकer so it करोesn't get clobbered */
	sg_list.list = scb->sg_list.list;
	cmd_busaddr = scb->scb_busaddr;
	/* copy in the CP */
	स_नकल(&scb->cmd, &pt->CoppCP.cmd, माप (IPS_IOCTL_CMD));
	/* FIX stuff that might be wrong */
	scb->sg_list.list = sg_list.list;
	scb->scb_busaddr = cmd_busaddr;
	scb->bus = scb->scsi_cmd->device->channel;
	scb->target_id = scb->scsi_cmd->device->id;
	scb->lun = scb->scsi_cmd->device->lun;
	scb->sg_len = 0;
	scb->data_len = 0;
	scb->flags = 0;
	scb->op_code = 0;
	scb->callback = ipsपूर्णांकr_करोne;
	scb->समयout = ips_cmd_समयout;

	scb->data_len = ha->flash_datasize;
	scb->data_busaddr =
	    dma_map_single(&ha->pcidev->dev, ha->flash_data, scb->data_len,
			   IPS_DMA_सूची(scb));
	scb->flags |= IPS_SCB_MAP_SINGLE;
	scb->cmd.flashfw.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.flashfw.buffer_addr = cpu_to_le32(scb->data_busaddr);
	अगर (pt->TimeOut)
		scb->समयout = pt->TimeOut;
	scb->scsi_cmd->result = DID_OK << 16;
	वापस IPS_SUCCESS;
पूर्ण

/****************************************************************************/
/* Routine Name: ips_मुक्त_flash_copperhead                                  */
/* Routine Description:                                                     */
/*   release the memory resources used to hold the flash image              */
/****************************************************************************/
अटल व्योम
ips_मुक्त_flash_copperhead(ips_ha_t * ha)
अणु
	अगर (ha->flash_data == ips_FlashData)
		test_and_clear_bit(0, &ips_FlashDataInUse);
	अन्यथा अगर (ha->flash_data)
		dma_मुक्त_coherent(&ha->pcidev->dev, ha->flash_len,
				  ha->flash_data, ha->flash_busaddr);
	ha->flash_data = शून्य;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_usrcmd                                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Process a user command and make it पढ़ोy to send                       */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_usrcmd(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
अणु
	IPS_SG_LIST sg_list;
	uपूर्णांक32_t cmd_busaddr;

	METHOD_TRACE("ips_usrcmd", 1);

	अगर ((!scb) || (!pt) || (!ha))
		वापस (0);

	/* Save the S/G list poपूर्णांकer so it करोesn't get clobbered */
	sg_list.list = scb->sg_list.list;
	cmd_busaddr = scb->scb_busaddr;
	/* copy in the CP */
	स_नकल(&scb->cmd, &pt->CoppCP.cmd, माप (IPS_IOCTL_CMD));
	स_नकल(&scb->dcdb, &pt->CoppCP.dcdb, माप (IPS_DCDB_TABLE));

	/* FIX stuff that might be wrong */
	scb->sg_list.list = sg_list.list;
	scb->scb_busaddr = cmd_busaddr;
	scb->bus = scb->scsi_cmd->device->channel;
	scb->target_id = scb->scsi_cmd->device->id;
	scb->lun = scb->scsi_cmd->device->lun;
	scb->sg_len = 0;
	scb->data_len = 0;
	scb->flags = 0;
	scb->op_code = 0;
	scb->callback = ipsपूर्णांकr_करोne;
	scb->समयout = ips_cmd_समयout;
	scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);

	/* we करोn't support DCDB/READ/WRITE Scatter Gather */
	अगर ((scb->cmd.basic_io.op_code == IPS_CMD_READ_SG) ||
	    (scb->cmd.basic_io.op_code == IPS_CMD_WRITE_SG) ||
	    (scb->cmd.basic_io.op_code == IPS_CMD_DCDB_SG))
		वापस (0);

	अगर (pt->CmdBSize) अणु
		scb->data_len = pt->CmdBSize;
		scb->data_busaddr = ha->ioctl_busaddr + माप (ips_passthru_t);
	पूर्ण अन्यथा अणु
		scb->data_busaddr = 0L;
	पूर्ण

	अगर (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)
		scb->cmd.dcdb.dcdb_address = cpu_to_le32(scb->scb_busaddr +
							 (अचिन्हित दीर्घ) &scb->
							 dcdb -
							 (अचिन्हित दीर्घ) scb);

	अगर (pt->CmdBSize) अणु
		अगर (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)
			scb->dcdb.buffer_poपूर्णांकer =
			    cpu_to_le32(scb->data_busaddr);
		अन्यथा
			scb->cmd.basic_io.sg_addr =
			    cpu_to_le32(scb->data_busaddr);
	पूर्ण

	/* set समयouts */
	अगर (pt->TimeOut) अणु
		scb->समयout = pt->TimeOut;

		अगर (pt->TimeOut <= 10)
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT10;
		अन्यथा अगर (pt->TimeOut <= 60)
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT60;
		अन्यथा
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT20M;
	पूर्ण

	/* assume success */
	scb->scsi_cmd->result = DID_OK << 16;

	/* success */
	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_cleanup_passthru                                       */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Cleanup after a passthru command                                       */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_cleanup_passthru(ips_ha_t * ha, ips_scb_t * scb)
अणु
	ips_passthru_t *pt;

	METHOD_TRACE("ips_cleanup_passthru", 1);

	अगर ((!scb) || (!scb->scsi_cmd) || (!scsi_sglist(scb->scsi_cmd))) अणु
		DEBUG_VAR(1, "(%s%d) couldn't cleanup after passthru",
			  ips_name, ha->host_num);

		वापस;
	पूर्ण
	pt = (ips_passthru_t *) ha->ioctl_data;

	/* Copy data back to the user */
	अगर (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)	/* Copy DCDB Back to Caller's Area */
		स_नकल(&pt->CoppCP.dcdb, &scb->dcdb, माप (IPS_DCDB_TABLE));

	pt->BasicStatus = scb->basic_status;
	pt->ExtendedStatus = scb->extended_status;
	pt->AdapterType = ha->ad_type;

	अगर (ha->pcidev->device == IPS_DEVICEID_COPPERHEAD &&
	    (scb->cmd.flashfw.op_code == IPS_CMD_DOWNLOAD ||
	     scb->cmd.flashfw.op_code == IPS_CMD_RW_BIOSFW))
		ips_मुक्त_flash_copperhead(ha);

	ips_scmd_buf_ग_लिखो(scb->scsi_cmd, ha->ioctl_data, ha->ioctl_datasize);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_host_info                                              */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   The passthru पूर्णांकerface क्रम the driver                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_host_info(ips_ha_t *ha, काष्ठा seq_file *m)
अणु
	METHOD_TRACE("ips_host_info", 1);

	seq_माला_दो(m, "\nIBM ServeRAID General Information:\n\n");

	अगर ((le32_to_cpu(ha->nvram->signature) == IPS_NVRAM_P5_SIG) &&
	    (le16_to_cpu(ha->nvram->adapter_type) != 0))
		seq_म_लिखो(m, "\tController Type                   : %s\n",
			  ips_adapter_name[ha->ad_type - 1]);
	अन्यथा
		seq_माला_दो(m, "\tController Type                   : Unknown\n");

	अगर (ha->io_addr)
		seq_म_लिखो(m,
			  "\tIO region                         : 0x%x (%d bytes)\n",
			  ha->io_addr, ha->io_len);

	अगर (ha->mem_addr) अणु
		seq_म_लिखो(m,
			  "\tMemory region                     : 0x%x (%d bytes)\n",
			  ha->mem_addr, ha->mem_len);
		seq_म_लिखो(m,
			  "\tShared memory address             : 0x%lx\n",
			  (अचिन्हित दीर्घ)ha->mem_ptr);
	पूर्ण

	seq_म_लिखो(m, "\tIRQ number                        : %d\n", ha->pcidev->irq);

    /* For the Next 3 lines Check क्रम Binary 0 at the end and करोn't include it if it's there. */
    /* That keeps everything happy क्रम "text" operations on the proc file.                    */

	अगर (le32_to_cpu(ha->nvram->signature) == IPS_NVRAM_P5_SIG) अणु
	अगर (ha->nvram->bios_low[3] == 0) अणु
		seq_म_लिखो(m,
			  "\tBIOS Version                      : %c%c%c%c%c%c%c\n",
			  ha->nvram->bios_high[0], ha->nvram->bios_high[1],
			  ha->nvram->bios_high[2], ha->nvram->bios_high[3],
			  ha->nvram->bios_low[0], ha->nvram->bios_low[1],
			  ha->nvram->bios_low[2]);

        पूर्ण अन्यथा अणु
		seq_म_लिखो(m,
			  "\tBIOS Version                      : %c%c%c%c%c%c%c%c\n",
			  ha->nvram->bios_high[0], ha->nvram->bios_high[1],
			  ha->nvram->bios_high[2], ha->nvram->bios_high[3],
			  ha->nvram->bios_low[0], ha->nvram->bios_low[1],
			  ha->nvram->bios_low[2], ha->nvram->bios_low[3]);
        पूर्ण

    पूर्ण

    अगर (ha->enq->CodeBlkVersion[7] == 0) अणु
        seq_म_लिखो(m,
		  "\tFirmware Version                  : %c%c%c%c%c%c%c\n",
		  ha->enq->CodeBlkVersion[0], ha->enq->CodeBlkVersion[1],
		  ha->enq->CodeBlkVersion[2], ha->enq->CodeBlkVersion[3],
		  ha->enq->CodeBlkVersion[4], ha->enq->CodeBlkVersion[5],
		  ha->enq->CodeBlkVersion[6]);
    पूर्ण अन्यथा अणु
	seq_म_लिखो(m,
		  "\tFirmware Version                  : %c%c%c%c%c%c%c%c\n",
		  ha->enq->CodeBlkVersion[0], ha->enq->CodeBlkVersion[1],
		  ha->enq->CodeBlkVersion[2], ha->enq->CodeBlkVersion[3],
		  ha->enq->CodeBlkVersion[4], ha->enq->CodeBlkVersion[5],
		  ha->enq->CodeBlkVersion[6], ha->enq->CodeBlkVersion[7]);
    पूर्ण

    अगर (ha->enq->BootBlkVersion[7] == 0) अणु
        seq_म_लिखो(m,
		  "\tBoot Block Version                : %c%c%c%c%c%c%c\n",
		  ha->enq->BootBlkVersion[0], ha->enq->BootBlkVersion[1],
		  ha->enq->BootBlkVersion[2], ha->enq->BootBlkVersion[3],
		  ha->enq->BootBlkVersion[4], ha->enq->BootBlkVersion[5],
		  ha->enq->BootBlkVersion[6]);
    पूर्ण अन्यथा अणु
        seq_म_लिखो(m,
		  "\tBoot Block Version                : %c%c%c%c%c%c%c%c\n",
		  ha->enq->BootBlkVersion[0], ha->enq->BootBlkVersion[1],
		  ha->enq->BootBlkVersion[2], ha->enq->BootBlkVersion[3],
		  ha->enq->BootBlkVersion[4], ha->enq->BootBlkVersion[5],
		  ha->enq->BootBlkVersion[6], ha->enq->BootBlkVersion[7]);
    पूर्ण

	seq_म_लिखो(m, "\tDriver Version                    : %s%s\n",
		  IPS_VERSION_HIGH, IPS_VERSION_LOW);

	seq_म_लिखो(m, "\tDriver Build                      : %d\n",
		  IPS_BUILD_IDENT);

	seq_म_लिखो(m, "\tMax Physical Devices              : %d\n",
		  ha->enq->ucMaxPhysicalDevices);
	seq_म_लिखो(m, "\tMax Active Commands               : %d\n",
		  ha->max_cmds);
	seq_म_लिखो(m, "\tCurrent Queued Commands           : %d\n",
		  ha->scb_रुकोlist.count);
	seq_म_लिखो(m, "\tCurrent Active Commands           : %d\n",
		  ha->scb_activelist.count - ha->num_ioctl);
	seq_म_लिखो(m, "\tCurrent Queued PT Commands        : %d\n",
		  ha->copp_रुकोlist.count);
	seq_म_लिखो(m, "\tCurrent Active PT Commands        : %d\n",
		  ha->num_ioctl);

	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_identअगरy_controller                                    */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Identअगरy this controller                                               */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_identअगरy_controller(ips_ha_t * ha)
अणु
	METHOD_TRACE("ips_identify_controller", 1);

	चयन (ha->pcidev->device) अणु
	हाल IPS_DEVICEID_COPPERHEAD:
		अगर (ha->pcidev->revision <= IPS_REVID_SERVERAID) अणु
			ha->ad_type = IPS_ADTYPE_SERVERAID;
		पूर्ण अन्यथा अगर (ha->pcidev->revision == IPS_REVID_SERVERAID2) अणु
			ha->ad_type = IPS_ADTYPE_SERVERAID2;
		पूर्ण अन्यथा अगर (ha->pcidev->revision == IPS_REVID_NAVAJO) अणु
			ha->ad_type = IPS_ADTYPE_NAVAJO;
		पूर्ण अन्यथा अगर ((ha->pcidev->revision == IPS_REVID_SERVERAID2)
			   && (ha->slot_num == 0)) अणु
			ha->ad_type = IPS_ADTYPE_KIOWA;
		पूर्ण अन्यथा अगर ((ha->pcidev->revision >= IPS_REVID_CLARINETP1) &&
			   (ha->pcidev->revision <= IPS_REVID_CLARINETP3)) अणु
			अगर (ha->enq->ucMaxPhysicalDevices == 15)
				ha->ad_type = IPS_ADTYPE_SERVERAID3L;
			अन्यथा
				ha->ad_type = IPS_ADTYPE_SERVERAID3;
		पूर्ण अन्यथा अगर ((ha->pcidev->revision >= IPS_REVID_TROMBONE32) &&
			   (ha->pcidev->revision <= IPS_REVID_TROMBONE64)) अणु
			ha->ad_type = IPS_ADTYPE_SERVERAID4H;
		पूर्ण
		अवरोध;

	हाल IPS_DEVICEID_MORPHEUS:
		चयन (ha->pcidev->subप्रणाली_device) अणु
		हाल IPS_SUBDEVICEID_4L:
			ha->ad_type = IPS_ADTYPE_SERVERAID4L;
			अवरोध;

		हाल IPS_SUBDEVICEID_4M:
			ha->ad_type = IPS_ADTYPE_SERVERAID4M;
			अवरोध;

		हाल IPS_SUBDEVICEID_4MX:
			ha->ad_type = IPS_ADTYPE_SERVERAID4MX;
			अवरोध;

		हाल IPS_SUBDEVICEID_4LX:
			ha->ad_type = IPS_ADTYPE_SERVERAID4LX;
			अवरोध;

		हाल IPS_SUBDEVICEID_5I2:
			ha->ad_type = IPS_ADTYPE_SERVERAID5I2;
			अवरोध;

		हाल IPS_SUBDEVICEID_5I1:
			ha->ad_type = IPS_ADTYPE_SERVERAID5I1;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल IPS_DEVICEID_MARCO:
		चयन (ha->pcidev->subप्रणाली_device) अणु
		हाल IPS_SUBDEVICEID_6M:
			ha->ad_type = IPS_ADTYPE_SERVERAID6M;
			अवरोध;
		हाल IPS_SUBDEVICEID_6I:
			ha->ad_type = IPS_ADTYPE_SERVERAID6I;
			अवरोध;
		हाल IPS_SUBDEVICEID_7k:
			ha->ad_type = IPS_ADTYPE_SERVERAID7k;
			अवरोध;
		हाल IPS_SUBDEVICEID_7M:
			ha->ad_type = IPS_ADTYPE_SERVERAID7M;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_get_bios_version                                       */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Get the BIOS revision number                                           */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_get_bios_version(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;
	पूर्णांक ret;
	uपूर्णांक8_t major;
	uपूर्णांक8_t minor;
	uपूर्णांक8_t subminor;
	uपूर्णांक8_t *buffer;

	METHOD_TRACE("ips_get_bios_version", 1);

	major = 0;
	minor = 0;

	स_नकल(ha->bios_version, "       ?", 8);

	अगर (ha->pcidev->device == IPS_DEVICEID_COPPERHEAD) अणु
		अगर (IPS_USE_MEMIO(ha)) अणु
			/* Memory Mapped I/O */

			/* test 1st byte */
			ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			अगर (पढ़ोb(ha->mem_ptr + IPS_REG_FLDP) != 0x55)
				वापस;

			ग_लिखोl(1, ha->mem_ptr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			अगर (पढ़ोb(ha->mem_ptr + IPS_REG_FLDP) != 0xAA)
				वापस;

			/* Get Major version */
			ग_लिखोl(0x1FF, ha->mem_ptr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			major = पढ़ोb(ha->mem_ptr + IPS_REG_FLDP);

			/* Get Minor version */
			ग_लिखोl(0x1FE, ha->mem_ptr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */
			minor = पढ़ोb(ha->mem_ptr + IPS_REG_FLDP);

			/* Get SubMinor version */
			ग_लिखोl(0x1FD, ha->mem_ptr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */
			subminor = पढ़ोb(ha->mem_ptr + IPS_REG_FLDP);

		पूर्ण अन्यथा अणु
			/* Programmed I/O */

			/* test 1st byte */
			outl(0, ha->io_addr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			अगर (inb(ha->io_addr + IPS_REG_FLDP) != 0x55)
				वापस;

			outl(1, ha->io_addr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			अगर (inb(ha->io_addr + IPS_REG_FLDP) != 0xAA)
				वापस;

			/* Get Major version */
			outl(0x1FF, ha->io_addr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			major = inb(ha->io_addr + IPS_REG_FLDP);

			/* Get Minor version */
			outl(0x1FE, ha->io_addr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			minor = inb(ha->io_addr + IPS_REG_FLDP);

			/* Get SubMinor version */
			outl(0x1FD, ha->io_addr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			subminor = inb(ha->io_addr + IPS_REG_FLDP);

		पूर्ण
	पूर्ण अन्यथा अणु
		/* Morpheus Family - Send Command to the card */

		buffer = ha->ioctl_data;

		स_रखो(buffer, 0, 0x1000);

		scb = &ha->scbs[ha->max_cmds - 1];

		ips_init_scb(ha, scb);

		scb->समयout = ips_cmd_समयout;
		scb->cdb[0] = IPS_CMD_RW_BIOSFW;

		scb->cmd.flashfw.op_code = IPS_CMD_RW_BIOSFW;
		scb->cmd.flashfw.command_id = IPS_COMMAND_ID(ha, scb);
		scb->cmd.flashfw.type = 1;
		scb->cmd.flashfw.direction = 0;
		scb->cmd.flashfw.count = cpu_to_le32(0x800);
		scb->cmd.flashfw.total_packets = 1;
		scb->cmd.flashfw.packet_num = 0;
		scb->data_len = 0x1000;
		scb->cmd.flashfw.buffer_addr = ha->ioctl_busaddr;

		/* issue the command */
		अगर (((ret =
		      ips_send_रुको(ha, scb, ips_cmd_समयout,
				    पूर्णांकr)) == IPS_FAILURE)
		    || (ret == IPS_SUCCESS_IMM)
		    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1)) अणु
			/* Error occurred */

			वापस;
		पूर्ण

		अगर ((buffer[0xC0] == 0x55) && (buffer[0xC1] == 0xAA)) अणु
			major = buffer[0x1ff + 0xC0];	/* Offset 0x1ff after the header (0xc0) */
			minor = buffer[0x1fe + 0xC0];	/* Offset 0x1fe after the header (0xc0) */
			subminor = buffer[0x1fd + 0xC0];	/* Offset 0x1fd after the header (0xc0) */
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण

	ha->bios_version[0] = hex_asc_upper_hi(major);
	ha->bios_version[1] = '.';
	ha->bios_version[2] = hex_asc_upper_lo(major);
	ha->bios_version[3] = hex_asc_upper_lo(subminor);
	ha->bios_version[4] = '.';
	ha->bios_version[5] = hex_asc_upper_hi(minor);
	ha->bios_version[6] = hex_asc_upper_lo(minor);
	ha->bios_version[7] = 0;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_hainit                                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize the controller                                              */
/*                                                                          */
/* NOTE: Assumes to be called from with a lock                              */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_hainit(ips_ha_t * ha)
अणु
	पूर्णांक i;

	METHOD_TRACE("ips_hainit", 1);

	अगर (!ha)
		वापस (0);

	अगर (ha->func.statinit)
		(*ha->func.statinit) (ha);

	अगर (ha->func.enableपूर्णांक)
		(*ha->func.enableपूर्णांक) (ha);

	/* Send FFDC */
	ha->reset_count = 1;
	ha->last_ffdc = kसमय_get_real_seconds();
	ips_ffdc_reset(ha, IPS_INTR_IORL);

	अगर (!ips_पढ़ो_config(ha, IPS_INTR_IORL)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to read config from controller.\n");

		वापस (0);
	पूर्ण
	/* end अगर */
	अगर (!ips_पढ़ो_adapter_status(ha, IPS_INTR_IORL)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to read controller status.\n");

		वापस (0);
	पूर्ण

	/* Identअगरy this controller */
	ips_identअगरy_controller(ha);

	अगर (!ips_पढ़ो_subप्रणाली_parameters(ha, IPS_INTR_IORL)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to read subsystem parameters.\n");

		वापस (0);
	पूर्ण

	/* ग_लिखो nvram user page 5 */
	अगर (!ips_ग_लिखो_driver_status(ha, IPS_INTR_IORL)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to write driver info to controller.\n");

		वापस (0);
	पूर्ण

	/* If there are Logical Drives and a Reset Occurred, then an EraseStripeLock is Needed */
	अगर ((ha->conf->ucLogDriveCount > 0) && (ha->requires_esl == 1))
		ips_clear_adapter(ha, IPS_INTR_IORL);

	/* set limits on SID, LUN, BUS */
	ha->ntarमाला_लो = IPS_MAX_TARGETS + 1;
	ha->nlun = 1;
	ha->nbus = (ha->enq->ucMaxPhysicalDevices / IPS_MAX_TARGETS) + 1;

	चयन (ha->conf->logical_drive[0].ucStripeSize) अणु
	हाल 4:
		ha->max_xfer = 0x10000;
		अवरोध;

	हाल 5:
		ha->max_xfer = 0x20000;
		अवरोध;

	हाल 6:
		ha->max_xfer = 0x40000;
		अवरोध;

	हाल 7:
	शेष:
		ha->max_xfer = 0x80000;
		अवरोध;
	पूर्ण

	/* setup max concurrent commands */
	अगर (le32_to_cpu(ha->subsys->param[4]) & 0x1) अणु
		/* Use the new method */
		ha->max_cmds = ha->enq->ucConcurrentCmdCount;
	पूर्ण अन्यथा अणु
		/* use the old method */
		चयन (ha->conf->logical_drive[0].ucStripeSize) अणु
		हाल 4:
			ha->max_cmds = 32;
			अवरोध;

		हाल 5:
			ha->max_cmds = 16;
			अवरोध;

		हाल 6:
			ha->max_cmds = 8;
			अवरोध;

		हाल 7:
		शेष:
			ha->max_cmds = 4;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Limit the Active Commands on a Lite Adapter */
	अगर ((ha->ad_type == IPS_ADTYPE_SERVERAID3L) ||
	    (ha->ad_type == IPS_ADTYPE_SERVERAID4L) ||
	    (ha->ad_type == IPS_ADTYPE_SERVERAID4LX)) अणु
		अगर ((ha->max_cmds > MaxLiteCmds) && (MaxLiteCmds))
			ha->max_cmds = MaxLiteCmds;
	पूर्ण

	/* set controller IDs */
	ha->ha_id[0] = IPS_ADAPTER_ID;
	क्रम (i = 1; i < ha->nbus; i++) अणु
		ha->ha_id[i] = ha->conf->init_id[i - 1] & 0x1f;
		ha->dcdb_active[i - 1] = 0;
	पूर्ण

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_next                                                   */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Take the next command off the queue and send it to the controller      */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_next(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;
	काष्ठा scsi_cmnd *SC;
	काष्ठा scsi_cmnd *p;
	काष्ठा scsi_cmnd *q;
	ips_copp_रुको_item_t *item;
	पूर्णांक ret;
	काष्ठा Scsi_Host *host;
	METHOD_TRACE("ips_next", 1);

	अगर (!ha)
		वापस;
	host = ips_sh[ha->host_num];
	/*
	 * Block access to the queue function so
	 * this command won't समय out
	 */
	अगर (पूर्णांकr == IPS_INTR_ON)
		spin_lock(host->host_lock);

	अगर ((ha->subsys->param[3] & 0x300000)
	    && (ha->scb_activelist.count == 0)) अणु
		समय64_t now = kसमय_get_real_seconds();
		अगर (now - ha->last_ffdc > IPS_SECS_8HOURS) अणु
			ha->last_ffdc = now;
			ips_ffdc_समय(ha);
		पूर्ण
	पूर्ण

	/*
	 * Send passthru commands
	 * These have priority over normal I/O
	 * but shouldn't affect perक्रमmance too much
	 * since we limit the number that can be active
	 * on the card at any one समय
	 */
	जबतक ((ha->num_ioctl < IPS_MAX_IOCTL) &&
	       (ha->copp_रुकोlist.head) && (scb = ips_माला_लोcb(ha))) अणु

		item = ips_हटाओq_copp_head(&ha->copp_रुकोlist);
		ha->num_ioctl++;
		अगर (पूर्णांकr == IPS_INTR_ON)
			spin_unlock(host->host_lock);
		scb->scsi_cmd = item->scsi_cmd;
		kमुक्त(item);

		ret = ips_make_passthru(ha, scb->scsi_cmd, scb, पूर्णांकr);

		अगर (पूर्णांकr == IPS_INTR_ON)
			spin_lock(host->host_lock);
		चयन (ret) अणु
		हाल IPS_FAILURE:
			अगर (scb->scsi_cmd) अणु
				scb->scsi_cmd->result = DID_ERROR << 16;
				scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
			पूर्ण

			ips_मुक्तscb(ha, scb);
			अवरोध;
		हाल IPS_SUCCESS_IMM:
			अगर (scb->scsi_cmd) अणु
				scb->scsi_cmd->result = DID_OK << 16;
				scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
			पूर्ण

			ips_मुक्तscb(ha, scb);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण		/* end हाल */

		अगर (ret != IPS_SUCCESS) अणु
			ha->num_ioctl--;
			जारी;
		पूर्ण

		ret = ips_send_cmd(ha, scb);

		अगर (ret == IPS_SUCCESS)
			ips_putq_scb_head(&ha->scb_activelist, scb);
		अन्यथा
			ha->num_ioctl--;

		चयन (ret) अणु
		हाल IPS_FAILURE:
			अगर (scb->scsi_cmd) अणु
				scb->scsi_cmd->result = DID_ERROR << 16;
			पूर्ण

			ips_मुक्तscb(ha, scb);
			अवरोध;
		हाल IPS_SUCCESS_IMM:
			ips_मुक्तscb(ha, scb);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण		/* end हाल */

	पूर्ण

	/*
	 * Send "Normal" I/O commands
	 */

	p = ha->scb_रुकोlist.head;
	जबतक ((p) && (scb = ips_माला_लोcb(ha))) अणु
		अगर ((scmd_channel(p) > 0)
		    && (ha->
			dcdb_active[scmd_channel(p) -
				    1] & (1 << scmd_id(p)))) अणु
			ips_मुक्तscb(ha, scb);
			p = (काष्ठा scsi_cmnd *) p->host_scribble;
			जारी;
		पूर्ण

		q = p;
		SC = ips_हटाओq_रुको(&ha->scb_रुकोlist, q);

		अगर (पूर्णांकr == IPS_INTR_ON)
			spin_unlock(host->host_lock);	/* Unlock HA after command is taken off queue */

		SC->result = DID_OK;
		SC->host_scribble = शून्य;

		scb->target_id = SC->device->id;
		scb->lun = SC->device->lun;
		scb->bus = SC->device->channel;
		scb->scsi_cmd = SC;
		scb->अवरोधup = 0;
		scb->data_len = 0;
		scb->callback = ipsपूर्णांकr_करोne;
		scb->समयout = ips_cmd_समयout;
		स_रखो(&scb->cmd, 0, 16);

		/* copy in the CDB */
		स_नकल(scb->cdb, SC->cmnd, SC->cmd_len);

                scb->sg_count = scsi_dma_map(SC);
                BUG_ON(scb->sg_count < 0);
		अगर (scb->sg_count) अणु
			काष्ठा scatterlist *sg;
			पूर्णांक i;

			scb->flags |= IPS_SCB_MAP_SG;

                        scsi_क्रम_each_sg(SC, sg, scb->sg_count, i) अणु
				अगर (ips_fill_scb_sg_single
				    (ha, sg_dma_address(sg), scb, i,
				     sg_dma_len(sg)) < 0)
					अवरोध;
			पूर्ण
			scb->dcdb.transfer_length = scb->data_len;
		पूर्ण अन्यथा अणु
                        scb->data_busaddr = 0L;
                        scb->sg_len = 0;
                        scb->data_len = 0;
                        scb->dcdb.transfer_length = 0;
		पूर्ण

		scb->dcdb.cmd_attribute =
		    ips_command_direction[scb->scsi_cmd->cmnd[0]];

		/* Allow a WRITE BUFFER Command to Have no Data */
		/* This is Used by Tape Flash Utilites          */
		अगर ((scb->scsi_cmd->cmnd[0] == WRITE_BUFFER) &&
				(scb->data_len == 0))
			scb->dcdb.cmd_attribute = 0;

		अगर (!(scb->dcdb.cmd_attribute & 0x3))
			scb->dcdb.transfer_length = 0;

		अगर (scb->data_len >= IPS_MAX_XFER) अणु
			scb->dcdb.cmd_attribute |= IPS_TRANSFER64K;
			scb->dcdb.transfer_length = 0;
		पूर्ण
		अगर (पूर्णांकr == IPS_INTR_ON)
			spin_lock(host->host_lock);

		ret = ips_send_cmd(ha, scb);

		चयन (ret) अणु
		हाल IPS_SUCCESS:
			ips_putq_scb_head(&ha->scb_activelist, scb);
			अवरोध;
		हाल IPS_FAILURE:
			अगर (scb->scsi_cmd) अणु
				scb->scsi_cmd->result = DID_ERROR << 16;
				scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
			पूर्ण

			अगर (scb->bus)
				ha->dcdb_active[scb->bus - 1] &=
				    ~(1 << scb->target_id);

			ips_मुक्तscb(ha, scb);
			अवरोध;
		हाल IPS_SUCCESS_IMM:
			अगर (scb->scsi_cmd)
				scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);

			अगर (scb->bus)
				ha->dcdb_active[scb->bus - 1] &=
				    ~(1 << scb->target_id);

			ips_मुक्तscb(ha, scb);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण		/* end हाल */

		p = (काष्ठा scsi_cmnd *) p->host_scribble;

	पूर्ण			/* end जबतक */

	अगर (पूर्णांकr == IPS_INTR_ON)
		spin_unlock(host->host_lock);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_putq_scb_head                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Add an item to the head of the queue                                   */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_putq_scb_head(ips_scb_queue_t * queue, ips_scb_t * item)
अणु
	METHOD_TRACE("ips_putq_scb_head", 1);

	अगर (!item)
		वापस;

	item->q_next = queue->head;
	queue->head = item;

	अगर (!queue->tail)
		queue->tail = item;

	queue->count++;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_हटाओq_scb_head                                       */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove the head of the queue                                           */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल ips_scb_t *
ips_हटाओq_scb_head(ips_scb_queue_t * queue)
अणु
	ips_scb_t *item;

	METHOD_TRACE("ips_removeq_scb_head", 1);

	item = queue->head;

	अगर (!item) अणु
		वापस (शून्य);
	पूर्ण

	queue->head = item->q_next;
	item->q_next = शून्य;

	अगर (queue->tail == item)
		queue->tail = शून्य;

	queue->count--;

	वापस (item);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_हटाओq_scb                                            */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove an item from a queue                                            */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल ips_scb_t *
ips_हटाओq_scb(ips_scb_queue_t * queue, ips_scb_t * item)
अणु
	ips_scb_t *p;

	METHOD_TRACE("ips_removeq_scb", 1);

	अगर (!item)
		वापस (शून्य);

	अगर (item == queue->head) अणु
		वापस (ips_हटाओq_scb_head(queue));
	पूर्ण

	p = queue->head;

	जबतक ((p) && (item != p->q_next))
		p = p->q_next;

	अगर (p) अणु
		/* found a match */
		p->q_next = item->q_next;

		अगर (!item->q_next)
			queue->tail = p;

		item->q_next = शून्य;
		queue->count--;

		वापस (item);
	पूर्ण

	वापस (शून्य);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_putq_रुको_tail                                         */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Add an item to the tail of the queue                                   */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल व्योम ips_putq_रुको_tail(ips_रुको_queue_entry_t *queue, काष्ठा scsi_cmnd *item)
अणु
	METHOD_TRACE("ips_putq_wait_tail", 1);

	अगर (!item)
		वापस;

	item->host_scribble = शून्य;

	अगर (queue->tail)
		queue->tail->host_scribble = (अक्षर *) item;

	queue->tail = item;

	अगर (!queue->head)
		queue->head = item;

	queue->count++;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_हटाओq_रुको_head                                      */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove the head of the queue                                           */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल काष्ठा scsi_cmnd *ips_हटाओq_रुको_head(ips_रुको_queue_entry_t *queue)
अणु
	काष्ठा scsi_cmnd *item;

	METHOD_TRACE("ips_removeq_wait_head", 1);

	item = queue->head;

	अगर (!item) अणु
		वापस (शून्य);
	पूर्ण

	queue->head = (काष्ठा scsi_cmnd *) item->host_scribble;
	item->host_scribble = शून्य;

	अगर (queue->tail == item)
		queue->tail = शून्य;

	queue->count--;

	वापस (item);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_हटाओq_रुको                                           */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove an item from a queue                                            */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल काष्ठा scsi_cmnd *ips_हटाओq_रुको(ips_रुको_queue_entry_t *queue,
					  काष्ठा scsi_cmnd *item)
अणु
	काष्ठा scsi_cmnd *p;

	METHOD_TRACE("ips_removeq_wait", 1);

	अगर (!item)
		वापस (शून्य);

	अगर (item == queue->head) अणु
		वापस (ips_हटाओq_रुको_head(queue));
	पूर्ण

	p = queue->head;

	जबतक ((p) && (item != (काष्ठा scsi_cmnd *) p->host_scribble))
		p = (काष्ठा scsi_cmnd *) p->host_scribble;

	अगर (p) अणु
		/* found a match */
		p->host_scribble = item->host_scribble;

		अगर (!item->host_scribble)
			queue->tail = p;

		item->host_scribble = शून्य;
		queue->count--;

		वापस (item);
	पूर्ण

	वापस (शून्य);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_putq_copp_tail                                         */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Add an item to the tail of the queue                                   */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_putq_copp_tail(ips_copp_queue_t * queue, ips_copp_रुको_item_t * item)
अणु
	METHOD_TRACE("ips_putq_copp_tail", 1);

	अगर (!item)
		वापस;

	item->next = शून्य;

	अगर (queue->tail)
		queue->tail->next = item;

	queue->tail = item;

	अगर (!queue->head)
		queue->head = item;

	queue->count++;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_हटाओq_copp_head                                      */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove the head of the queue                                           */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल ips_copp_रुको_item_t *
ips_हटाओq_copp_head(ips_copp_queue_t * queue)
अणु
	ips_copp_रुको_item_t *item;

	METHOD_TRACE("ips_removeq_copp_head", 1);

	item = queue->head;

	अगर (!item) अणु
		वापस (शून्य);
	पूर्ण

	queue->head = item->next;
	item->next = शून्य;

	अगर (queue->tail == item)
		queue->tail = शून्य;

	queue->count--;

	वापस (item);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_हटाओq_copp                                           */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove an item from a queue                                            */
/*                                                                          */
/* ASSUMED to be called from within the HA lock                             */
/*                                                                          */
/****************************************************************************/
अटल ips_copp_रुको_item_t *
ips_हटाओq_copp(ips_copp_queue_t * queue, ips_copp_रुको_item_t * item)
अणु
	ips_copp_रुको_item_t *p;

	METHOD_TRACE("ips_removeq_copp", 1);

	अगर (!item)
		वापस (शून्य);

	अगर (item == queue->head) अणु
		वापस (ips_हटाओq_copp_head(queue));
	पूर्ण

	p = queue->head;

	जबतक ((p) && (item != p->next))
		p = p->next;

	अगर (p) अणु
		/* found a match */
		p->next = item->next;

		अगर (!item->next)
			queue->tail = p;

		item->next = शून्य;
		queue->count--;

		वापस (item);
	पूर्ण

	वापस (शून्य);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ipsपूर्णांकr_blocking                                           */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Finalize an पूर्णांकerrupt क्रम पूर्णांकernal commands                            */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ipsपूर्णांकr_blocking(ips_ha_t * ha, ips_scb_t * scb)
अणु
	METHOD_TRACE("ipsintr_blocking", 2);

	ips_मुक्तscb(ha, scb);
	अगर ((ha->रुकोflag == TRUE) && (ha->cmd_in_progress == scb->cdb[0])) अणु
		ha->रुकोflag = FALSE;

		वापस;
	पूर्ण
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ipsपूर्णांकr_करोne                                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Finalize an पूर्णांकerrupt क्रम non-पूर्णांकernal commands                        */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ipsपूर्णांकr_करोne(ips_ha_t * ha, ips_scb_t * scb)
अणु
	METHOD_TRACE("ipsintr_done", 2);

	अगर (!scb) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Spurious interrupt; scb NULL.\n");

		वापस;
	पूर्ण

	अगर (scb->scsi_cmd == शून्य) अणु
		/* unexpected पूर्णांकerrupt */
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Spurious interrupt; scsi_cmd not set.\n");

		वापस;
	पूर्ण

	ips_करोne(ha, scb);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_करोne                                                   */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Do housekeeping on completed commands                                  */
/*  ASSUMED to be called क्रमm within the request lock                       */
/****************************************************************************/
अटल व्योम
ips_करोne(ips_ha_t * ha, ips_scb_t * scb)
अणु
	पूर्णांक ret;

	METHOD_TRACE("ips_done", 1);

	अगर (!scb)
		वापस;

	अगर ((scb->scsi_cmd) && (ips_is_passthru(scb->scsi_cmd))) अणु
		ips_cleanup_passthru(ha, scb);
		ha->num_ioctl--;
	पूर्ण अन्यथा अणु
		/*
		 * Check to see अगर this command had too much
		 * data and had to be broke up.  If so, queue
		 * the rest of the data and जारी.
		 */
		अगर ((scb->अवरोधup) || (scb->sg_अवरोध)) अणु
                        काष्ठा scatterlist *sg;
                        पूर्णांक i, sg_dma_index, ips_sg_index = 0;

			/* we had a data अवरोधup */
			scb->data_len = 0;

                        sg = scsi_sglist(scb->scsi_cmd);

                        /* Spin क्रमward to last dma chunk */
                        sg_dma_index = scb->अवरोधup;
                        क्रम (i = 0; i < scb->अवरोधup; i++)
                                sg = sg_next(sg);

			/* Take care of possible partial on last chunk */
                        ips_fill_scb_sg_single(ha,
                                               sg_dma_address(sg),
                                               scb, ips_sg_index++,
                                               sg_dma_len(sg));

                        क्रम (; sg_dma_index < scsi_sg_count(scb->scsi_cmd);
                             sg_dma_index++, sg = sg_next(sg)) अणु
                                अगर (ips_fill_scb_sg_single
                                    (ha,
                                     sg_dma_address(sg),
                                     scb, ips_sg_index++,
                                     sg_dma_len(sg)) < 0)
                                        अवरोध;
                        पूर्ण

			scb->dcdb.transfer_length = scb->data_len;
			scb->dcdb.cmd_attribute |=
			    ips_command_direction[scb->scsi_cmd->cmnd[0]];

			अगर (!(scb->dcdb.cmd_attribute & 0x3))
				scb->dcdb.transfer_length = 0;

			अगर (scb->data_len >= IPS_MAX_XFER) अणु
				scb->dcdb.cmd_attribute |= IPS_TRANSFER64K;
				scb->dcdb.transfer_length = 0;
			पूर्ण

			ret = ips_send_cmd(ha, scb);

			चयन (ret) अणु
			हाल IPS_FAILURE:
				अगर (scb->scsi_cmd) अणु
					scb->scsi_cmd->result = DID_ERROR << 16;
					scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
				पूर्ण

				ips_मुक्तscb(ha, scb);
				अवरोध;
			हाल IPS_SUCCESS_IMM:
				अगर (scb->scsi_cmd) अणु
					scb->scsi_cmd->result = DID_ERROR << 16;
					scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);
				पूर्ण

				ips_मुक्तscb(ha, scb);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण	/* end हाल */

			वापस;
		पूर्ण
	पूर्ण			/* end अगर passthru */

	अगर (scb->bus) अणु
		ha->dcdb_active[scb->bus - 1] &= ~(1 << scb->target_id);
	पूर्ण

	scb->scsi_cmd->scsi_करोne(scb->scsi_cmd);

	ips_मुक्तscb(ha, scb);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_map_status                                             */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Map Controller Error codes to Linux Error Codes                        */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_map_status(ips_ha_t * ha, ips_scb_t * scb, ips_stat_t * sp)
अणु
	पूर्णांक errcode;
	पूर्णांक device_error;
	uपूर्णांक32_t transfer_len;
	IPS_DCDB_TABLE_TAPE *tapeDCDB;
	IPS_SCSI_INQ_DATA inquiryData;

	METHOD_TRACE("ips_map_status", 1);

	अगर (scb->bus) अणु
		DEBUG_VAR(2,
			  "(%s%d) Physical device error (%d %d %d): %x %x, Sense Key: %x, ASC: %x, ASCQ: %x",
			  ips_name, ha->host_num,
			  scb->scsi_cmd->device->channel,
			  scb->scsi_cmd->device->id, scb->scsi_cmd->device->lun,
			  scb->basic_status, scb->extended_status,
			  scb->extended_status ==
			  IPS_ERR_CKCOND ? scb->dcdb.sense_info[2] & 0xf : 0,
			  scb->extended_status ==
			  IPS_ERR_CKCOND ? scb->dcdb.sense_info[12] : 0,
			  scb->extended_status ==
			  IPS_ERR_CKCOND ? scb->dcdb.sense_info[13] : 0);
	पूर्ण

	/* शेष driver error */
	errcode = DID_ERROR;
	device_error = 0;

	चयन (scb->basic_status & IPS_GSC_STATUS_MASK) अणु
	हाल IPS_CMD_TIMEOUT:
		errcode = DID_TIME_OUT;
		अवरोध;

	हाल IPS_INVAL_OPCO:
	हाल IPS_INVAL_CMD_BLK:
	हाल IPS_INVAL_PARM_BLK:
	हाल IPS_LD_ERROR:
	हाल IPS_CMD_CMPLT_WERROR:
		अवरोध;

	हाल IPS_PHYS_DRV_ERROR:
		चयन (scb->extended_status) अणु
		हाल IPS_ERR_SEL_TO:
			अगर (scb->bus)
				errcode = DID_NO_CONNECT;

			अवरोध;

		हाल IPS_ERR_OU_RUN:
			अगर ((scb->cmd.dcdb.op_code == IPS_CMD_EXTENDED_DCDB) ||
			    (scb->cmd.dcdb.op_code ==
			     IPS_CMD_EXTENDED_DCDB_SG)) अणु
				tapeDCDB = (IPS_DCDB_TABLE_TAPE *) & scb->dcdb;
				transfer_len = tapeDCDB->transfer_length;
			पूर्ण अन्यथा अणु
				transfer_len =
				    (uपूर्णांक32_t) scb->dcdb.transfer_length;
			पूर्ण

			अगर ((scb->bus) && (transfer_len < scb->data_len)) अणु
				/* Underrun - set शेष to no error */
				errcode = DID_OK;

				/* Restrict access to physical DASD */
				अगर (scb->scsi_cmd->cmnd[0] == INQUIRY) अणु
				    ips_scmd_buf_पढ़ो(scb->scsi_cmd,
                                      &inquiryData, माप (inquiryData));
 				    अगर ((inquiryData.DeviceType & 0x1f) == TYPE_DISK) अणु
				        errcode = DID_TIME_OUT;
				        अवरोध;
				    पूर्ण
				पूर्ण
			पूर्ण अन्यथा
				errcode = DID_ERROR;

			अवरोध;

		हाल IPS_ERR_RECOVERY:
			/* करोn't fail recovered errors */
			अगर (scb->bus)
				errcode = DID_OK;

			अवरोध;

		हाल IPS_ERR_HOST_RESET:
		हाल IPS_ERR_DEV_RESET:
			errcode = DID_RESET;
			अवरोध;

		हाल IPS_ERR_CKCOND:
			अगर (scb->bus) अणु
				अगर ((scb->cmd.dcdb.op_code ==
				     IPS_CMD_EXTENDED_DCDB)
				    || (scb->cmd.dcdb.op_code ==
					IPS_CMD_EXTENDED_DCDB_SG)) अणु
					tapeDCDB =
					    (IPS_DCDB_TABLE_TAPE *) & scb->dcdb;
					स_नकल(scb->scsi_cmd->sense_buffer,
					       tapeDCDB->sense_info,
					       SCSI_SENSE_BUFFERSIZE);
				पूर्ण अन्यथा अणु
					स_नकल(scb->scsi_cmd->sense_buffer,
					       scb->dcdb.sense_info,
					       SCSI_SENSE_BUFFERSIZE);
				पूर्ण
				device_error = 2;	/* check condition */
			पूर्ण

			errcode = DID_OK;

			अवरोध;

		शेष:
			errcode = DID_ERROR;
			अवरोध;

		पूर्ण		/* end चयन */
	पूर्ण			/* end चयन */

	scb->scsi_cmd->result = device_error | (errcode << 16);

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_send_रुको                                              */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Send a command to the controller and रुको क्रम it to वापस             */
/*                                                                          */
/*   The FFDC Time Stamp use this function क्रम the callback, but करोesn't    */
/*   actually need to रुको.                                                 */
/****************************************************************************/
अटल पूर्णांक
ips_send_रुको(ips_ha_t * ha, ips_scb_t * scb, पूर्णांक समयout, पूर्णांक पूर्णांकr)
अणु
	पूर्णांक ret;

	METHOD_TRACE("ips_send_wait", 1);

	अगर (पूर्णांकr != IPS_FFDC) अणु	/* Won't be Waiting अगर this is a Time Stamp */
		ha->रुकोflag = TRUE;
		ha->cmd_in_progress = scb->cdb[0];
	पूर्ण
	scb->callback = ipsपूर्णांकr_blocking;
	ret = ips_send_cmd(ha, scb);

	अगर ((ret == IPS_FAILURE) || (ret == IPS_SUCCESS_IMM))
		वापस (ret);

	अगर (पूर्णांकr != IPS_FFDC)	/* Don't Wait around अगर this is a Time Stamp */
		ret = ips_रुको(ha, समयout, पूर्णांकr);

	वापस (ret);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_scmd_buf_ग_लिखो                                         */
/*                                                                          */
/* Routine Description:                                                     */
/*  Write data to काष्ठा scsi_cmnd request_buffer at proper offsets	    */
/****************************************************************************/
अटल व्योम
ips_scmd_buf_ग_लिखो(काष्ठा scsi_cmnd *scmd, व्योम *data, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	scsi_sg_copy_from_buffer(scmd, data, count);
	local_irq_restore(flags);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_scmd_buf_पढ़ो                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*  Copy data from a काष्ठा scsi_cmnd to a new, linear buffer		    */
/****************************************************************************/
अटल व्योम
ips_scmd_buf_पढ़ो(काष्ठा scsi_cmnd *scmd, व्योम *data, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	scsi_sg_copy_to_buffer(scmd, data, count);
	local_irq_restore(flags);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_send_cmd                                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Map SCSI commands to ServeRAID commands क्रम logical drives             */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_send_cmd(ips_ha_t * ha, ips_scb_t * scb)
अणु
	पूर्णांक ret;
	अक्षर *sp;
	पूर्णांक device_error;
	IPS_DCDB_TABLE_TAPE *tapeDCDB;
	पूर्णांक TimeOut;

	METHOD_TRACE("ips_send_cmd", 1);

	ret = IPS_SUCCESS;

	अगर (!scb->scsi_cmd) अणु
		/* पूर्णांकernal command */

		अगर (scb->bus > 0) अणु
			/* Controller commands can't be issued */
			/* to real devices -- fail them        */
			अगर ((ha->रुकोflag == TRUE) &&
			    (ha->cmd_in_progress == scb->cdb[0])) अणु
				ha->रुकोflag = FALSE;
			पूर्ण

			वापस (1);
		पूर्ण
	पूर्ण अन्यथा अगर ((scb->bus == 0) && (!ips_is_passthru(scb->scsi_cmd))) अणु
		/* command to logical bus -- पूर्णांकerpret */
		ret = IPS_SUCCESS_IMM;

		चयन (scb->scsi_cmd->cmnd[0]) अणु
		हाल ALLOW_MEDIUM_REMOVAL:
		हाल REZERO_UNIT:
		हाल ERASE:
		हाल WRITE_खाताMARKS:
		हाल SPACE:
			scb->scsi_cmd->result = DID_ERROR << 16;
			अवरोध;

		हाल START_STOP:
			scb->scsi_cmd->result = DID_OK << 16;
			अवरोध;

		हाल TEST_UNIT_READY:
		हाल INQUIRY:
			अगर (scb->target_id == IPS_ADAPTER_ID) अणु
				/*
				 * Either we have a TUR
				 * or we have a SCSI inquiry
				 */
				अगर (scb->scsi_cmd->cmnd[0] == TEST_UNIT_READY)
					scb->scsi_cmd->result = DID_OK << 16;

				अगर (scb->scsi_cmd->cmnd[0] == INQUIRY) अणु
					IPS_SCSI_INQ_DATA inquiry;

					स_रखो(&inquiry, 0,
					       माप (IPS_SCSI_INQ_DATA));

					inquiry.DeviceType =
					    IPS_SCSI_INQ_TYPE_PROCESSOR;
					inquiry.DeviceTypeQualअगरier =
					    IPS_SCSI_INQ_LU_CONNECTED;
					inquiry.Version = IPS_SCSI_INQ_REV2;
					inquiry.ResponseDataFormat =
					    IPS_SCSI_INQ_RD_REV2;
					inquiry.AdditionalLength = 31;
					inquiry.Flags[0] =
					    IPS_SCSI_INQ_Address16;
					inquiry.Flags[1] =
					    IPS_SCSI_INQ_WBus16 |
					    IPS_SCSI_INQ_Sync;
					स_नकल(inquiry.VenकरोrId, "IBM     ",
						8);
					स_नकल(inquiry.ProductId,
						"SERVERAID       ", 16);
					स_नकल(inquiry.ProductRevisionLevel,
						"1.00", 4);

					ips_scmd_buf_ग_लिखो(scb->scsi_cmd,
							   &inquiry,
							   माप (inquiry));

					scb->scsi_cmd->result = DID_OK << 16;
				पूर्ण
			पूर्ण अन्यथा अणु
				scb->cmd.logical_info.op_code = IPS_CMD_GET_LD_INFO;
				scb->cmd.logical_info.command_id = IPS_COMMAND_ID(ha, scb);
				scb->cmd.logical_info.reserved = 0;
				scb->cmd.logical_info.reserved2 = 0;
				scb->data_len = माप (IPS_LD_INFO);
				scb->data_busaddr = ha->logical_drive_info_dma_addr;
				scb->flags = 0;
				scb->cmd.logical_info.buffer_addr = scb->data_busaddr;
				ret = IPS_SUCCESS;
			पूर्ण

			अवरोध;

		हाल REQUEST_SENSE:
			ips_reqsen(ha, scb);
			scb->scsi_cmd->result = DID_OK << 16;
			अवरोध;

		हाल READ_6:
		हाल WRITE_6:
			अगर (!scb->sg_len) अणु
				scb->cmd.basic_io.op_code =
				    (scb->scsi_cmd->cmnd[0] ==
				     READ_6) ? IPS_CMD_READ : IPS_CMD_WRITE;
				scb->cmd.basic_io.enhanced_sg = 0;
				scb->cmd.basic_io.sg_addr =
				    cpu_to_le32(scb->data_busaddr);
			पूर्ण अन्यथा अणु
				scb->cmd.basic_io.op_code =
				    (scb->scsi_cmd->cmnd[0] ==
				     READ_6) ? IPS_CMD_READ_SG :
				    IPS_CMD_WRITE_SG;
				scb->cmd.basic_io.enhanced_sg =
				    IPS_USE_ENH_SGLIST(ha) ? 0xFF : 0;
				scb->cmd.basic_io.sg_addr =
				    cpu_to_le32(scb->sg_busaddr);
			पूर्ण

			scb->cmd.basic_io.segment_4G = 0;
			scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);
			scb->cmd.basic_io.log_drv = scb->target_id;
			scb->cmd.basic_io.sg_count = scb->sg_len;

			अगर (scb->cmd.basic_io.lba)
				le32_add_cpu(&scb->cmd.basic_io.lba,
						le16_to_cpu(scb->cmd.basic_io.
							    sector_count));
			अन्यथा
				scb->cmd.basic_io.lba =
				    (((scb->scsi_cmd->
				       cmnd[1] & 0x1f) << 16) | (scb->scsi_cmd->
								 cmnd[2] << 8) |
				     (scb->scsi_cmd->cmnd[3]));

			scb->cmd.basic_io.sector_count =
			    cpu_to_le16(scb->data_len / IPS_BLKSIZE);

			अगर (le16_to_cpu(scb->cmd.basic_io.sector_count) == 0)
				scb->cmd.basic_io.sector_count =
				    cpu_to_le16(256);

			ret = IPS_SUCCESS;
			अवरोध;

		हाल READ_10:
		हाल WRITE_10:
			अगर (!scb->sg_len) अणु
				scb->cmd.basic_io.op_code =
				    (scb->scsi_cmd->cmnd[0] ==
				     READ_10) ? IPS_CMD_READ : IPS_CMD_WRITE;
				scb->cmd.basic_io.enhanced_sg = 0;
				scb->cmd.basic_io.sg_addr =
				    cpu_to_le32(scb->data_busaddr);
			पूर्ण अन्यथा अणु
				scb->cmd.basic_io.op_code =
				    (scb->scsi_cmd->cmnd[0] ==
				     READ_10) ? IPS_CMD_READ_SG :
				    IPS_CMD_WRITE_SG;
				scb->cmd.basic_io.enhanced_sg =
				    IPS_USE_ENH_SGLIST(ha) ? 0xFF : 0;
				scb->cmd.basic_io.sg_addr =
				    cpu_to_le32(scb->sg_busaddr);
			पूर्ण

			scb->cmd.basic_io.segment_4G = 0;
			scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);
			scb->cmd.basic_io.log_drv = scb->target_id;
			scb->cmd.basic_io.sg_count = scb->sg_len;

			अगर (scb->cmd.basic_io.lba)
				le32_add_cpu(&scb->cmd.basic_io.lba,
						le16_to_cpu(scb->cmd.basic_io.
							    sector_count));
			अन्यथा
				scb->cmd.basic_io.lba =
				    ((scb->scsi_cmd->cmnd[2] << 24) | (scb->
								       scsi_cmd->
								       cmnd[3]
								       << 16) |
				     (scb->scsi_cmd->cmnd[4] << 8) | scb->
				     scsi_cmd->cmnd[5]);

			scb->cmd.basic_io.sector_count =
			    cpu_to_le16(scb->data_len / IPS_BLKSIZE);

			अगर (cpu_to_le16(scb->cmd.basic_io.sector_count) == 0) अणु
				/*
				 * This is a null condition
				 * we करोn't have to करो anything
				 * so just वापस
				 */
				scb->scsi_cmd->result = DID_OK << 16;
			पूर्ण अन्यथा
				ret = IPS_SUCCESS;

			अवरोध;

		हाल RESERVE:
		हाल RELEASE:
			scb->scsi_cmd->result = DID_OK << 16;
			अवरोध;

		हाल MODE_SENSE:
			scb->cmd.basic_io.op_code = IPS_CMD_ENQUIRY;
			scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);
			scb->cmd.basic_io.segment_4G = 0;
			scb->cmd.basic_io.enhanced_sg = 0;
			scb->data_len = माप (*ha->enq);
			scb->cmd.basic_io.sg_addr = ha->enq_busaddr;
			ret = IPS_SUCCESS;
			अवरोध;

		हाल READ_CAPACITY:
			scb->cmd.logical_info.op_code = IPS_CMD_GET_LD_INFO;
			scb->cmd.logical_info.command_id = IPS_COMMAND_ID(ha, scb);
			scb->cmd.logical_info.reserved = 0;
			scb->cmd.logical_info.reserved2 = 0;
			scb->cmd.logical_info.reserved3 = 0;
			scb->data_len = माप (IPS_LD_INFO);
			scb->data_busaddr = ha->logical_drive_info_dma_addr;
			scb->flags = 0;
			scb->cmd.logical_info.buffer_addr = scb->data_busaddr;
			ret = IPS_SUCCESS;
			अवरोध;

		हाल SEND_DIAGNOSTIC:
		हाल REASSIGN_BLOCKS:
		हाल FORMAT_UNIT:
		हाल SEEK_10:
		हाल VERIFY:
		हाल READ_DEFECT_DATA:
		हाल READ_BUFFER:
		हाल WRITE_BUFFER:
			scb->scsi_cmd->result = DID_OK << 16;
			अवरोध;

		शेष:
			/* Set the Return Info to appear like the Command was */
			/* attempted, a Check Condition occurred, and Sense   */
			/* Data indicating an Invalid CDB OpCode is वापसed. */
			sp = (अक्षर *) scb->scsi_cmd->sense_buffer;

			sp[0] = 0x70;	/* Error Code               */
			sp[2] = ILLEGAL_REQUEST;	/* Sense Key 5 Illegal Req. */
			sp[7] = 0x0A;	/* Additional Sense Length  */
			sp[12] = 0x20;	/* ASC = Invalid OpCode     */
			sp[13] = 0x00;	/* ASCQ                     */

			device_error = 2;	/* Indicate Check Condition */
			scb->scsi_cmd->result = device_error | (DID_OK << 16);
			अवरोध;
		पूर्ण		/* end चयन */
	पूर्ण
	/* end अगर */
	अगर (ret == IPS_SUCCESS_IMM)
		वापस (ret);

	/* setup DCDB */
	अगर (scb->bus > 0) अणु

		/* If we alपढ़ोy know the Device is Not there, no need to attempt a Command   */
		/* This also protects an NT FailOver Controller from getting CDB's sent to it */
		अगर (ha->conf->dev[scb->bus - 1][scb->target_id].ucState == 0) अणु
			scb->scsi_cmd->result = DID_NO_CONNECT << 16;
			वापस (IPS_SUCCESS_IMM);
		पूर्ण

		ha->dcdb_active[scb->bus - 1] |= (1 << scb->target_id);
		scb->cmd.dcdb.command_id = IPS_COMMAND_ID(ha, scb);
		scb->cmd.dcdb.dcdb_address = cpu_to_le32(scb->scb_busaddr +
							 (अचिन्हित दीर्घ) &scb->
							 dcdb -
							 (अचिन्हित दीर्घ) scb);
		scb->cmd.dcdb.reserved = 0;
		scb->cmd.dcdb.reserved2 = 0;
		scb->cmd.dcdb.reserved3 = 0;
		scb->cmd.dcdb.segment_4G = 0;
		scb->cmd.dcdb.enhanced_sg = 0;

		TimeOut = scb->scsi_cmd->request->समयout;

		अगर (ha->subsys->param[4] & 0x00100000) अणु	/* If NEW Tape DCDB is Supported */
			अगर (!scb->sg_len) अणु
				scb->cmd.dcdb.op_code = IPS_CMD_EXTENDED_DCDB;
			पूर्ण अन्यथा अणु
				scb->cmd.dcdb.op_code =
				    IPS_CMD_EXTENDED_DCDB_SG;
				scb->cmd.dcdb.enhanced_sg =
				    IPS_USE_ENH_SGLIST(ha) ? 0xFF : 0;
			पूर्ण

			tapeDCDB = (IPS_DCDB_TABLE_TAPE *) & scb->dcdb;	/* Use Same Data Area as Old DCDB Struct */
			tapeDCDB->device_address =
			    ((scb->bus - 1) << 4) | scb->target_id;
			tapeDCDB->cmd_attribute |= IPS_DISCONNECT_ALLOWED;
			tapeDCDB->cmd_attribute &= ~IPS_TRANSFER64K;	/* Always Turn OFF 64K Size Flag */

			अगर (TimeOut) अणु
				अगर (TimeOut < (10 * HZ))
					tapeDCDB->cmd_attribute |= IPS_TIMEOUT10;	/* TimeOut is 10 Seconds */
				अन्यथा अगर (TimeOut < (60 * HZ))
					tapeDCDB->cmd_attribute |= IPS_TIMEOUT60;	/* TimeOut is 60 Seconds */
				अन्यथा अगर (TimeOut < (1200 * HZ))
					tapeDCDB->cmd_attribute |= IPS_TIMEOUT20M;	/* TimeOut is 20 Minutes */
			पूर्ण

			tapeDCDB->cdb_length = scb->scsi_cmd->cmd_len;
			tapeDCDB->reserved_क्रम_LUN = 0;
			tapeDCDB->transfer_length = scb->data_len;
			अगर (scb->cmd.dcdb.op_code == IPS_CMD_EXTENDED_DCDB_SG)
				tapeDCDB->buffer_poपूर्णांकer =
				    cpu_to_le32(scb->sg_busaddr);
			अन्यथा
				tapeDCDB->buffer_poपूर्णांकer =
				    cpu_to_le32(scb->data_busaddr);
			tapeDCDB->sg_count = scb->sg_len;
			tapeDCDB->sense_length = माप (tapeDCDB->sense_info);
			tapeDCDB->scsi_status = 0;
			tapeDCDB->reserved = 0;
			स_नकल(tapeDCDB->scsi_cdb, scb->scsi_cmd->cmnd,
			       scb->scsi_cmd->cmd_len);
		पूर्ण अन्यथा अणु
			अगर (!scb->sg_len) अणु
				scb->cmd.dcdb.op_code = IPS_CMD_DCDB;
			पूर्ण अन्यथा अणु
				scb->cmd.dcdb.op_code = IPS_CMD_DCDB_SG;
				scb->cmd.dcdb.enhanced_sg =
				    IPS_USE_ENH_SGLIST(ha) ? 0xFF : 0;
			पूर्ण

			scb->dcdb.device_address =
			    ((scb->bus - 1) << 4) | scb->target_id;
			scb->dcdb.cmd_attribute |= IPS_DISCONNECT_ALLOWED;

			अगर (TimeOut) अणु
				अगर (TimeOut < (10 * HZ))
					scb->dcdb.cmd_attribute |= IPS_TIMEOUT10;	/* TimeOut is 10 Seconds */
				अन्यथा अगर (TimeOut < (60 * HZ))
					scb->dcdb.cmd_attribute |= IPS_TIMEOUT60;	/* TimeOut is 60 Seconds */
				अन्यथा अगर (TimeOut < (1200 * HZ))
					scb->dcdb.cmd_attribute |= IPS_TIMEOUT20M;	/* TimeOut is 20 Minutes */
			पूर्ण

			scb->dcdb.transfer_length = scb->data_len;
			अगर (scb->dcdb.cmd_attribute & IPS_TRANSFER64K)
				scb->dcdb.transfer_length = 0;
			अगर (scb->cmd.dcdb.op_code == IPS_CMD_DCDB_SG)
				scb->dcdb.buffer_poपूर्णांकer =
				    cpu_to_le32(scb->sg_busaddr);
			अन्यथा
				scb->dcdb.buffer_poपूर्णांकer =
				    cpu_to_le32(scb->data_busaddr);
			scb->dcdb.cdb_length = scb->scsi_cmd->cmd_len;
			scb->dcdb.sense_length = माप (scb->dcdb.sense_info);
			scb->dcdb.sg_count = scb->sg_len;
			scb->dcdb.reserved = 0;
			स_नकल(scb->dcdb.scsi_cdb, scb->scsi_cmd->cmnd,
			       scb->scsi_cmd->cmd_len);
			scb->dcdb.scsi_status = 0;
			scb->dcdb.reserved2[0] = 0;
			scb->dcdb.reserved2[1] = 0;
			scb->dcdb.reserved2[2] = 0;
		पूर्ण
	पूर्ण

	वापस ((*ha->func.issue) (ha, scb));
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_chk_status                                             */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Check the status of commands to logical drives                         */
/*   Assumed to be called with the HA lock                                  */
/****************************************************************************/
अटल व्योम
ips_chkstatus(ips_ha_t * ha, IPS_STATUS * pstatus)
अणु
	ips_scb_t *scb;
	ips_stat_t *sp;
	uपूर्णांक8_t basic_status;
	uपूर्णांक8_t ext_status;
	पूर्णांक errcode;
	IPS_SCSI_INQ_DATA inquiryData;

	METHOD_TRACE("ips_chkstatus", 1);

	scb = &ha->scbs[pstatus->fields.command_id];
	scb->basic_status = basic_status =
	    pstatus->fields.basic_status & IPS_BASIC_STATUS_MASK;
	scb->extended_status = ext_status = pstatus->fields.extended_status;

	sp = &ha->sp;
	sp->residue_len = 0;
	sp->scb_addr = (व्योम *) scb;

	/* Remove the item from the active queue */
	ips_हटाओq_scb(&ha->scb_activelist, scb);

	अगर (!scb->scsi_cmd)
		/* पूर्णांकernal commands are handled in करो_ipsपूर्णांकr */
		वापस;

	DEBUG_VAR(2, "(%s%d) ips_chkstatus: cmd 0x%X id %d (%d %d %d)",
		  ips_name,
		  ha->host_num,
		  scb->cdb[0],
		  scb->cmd.basic_io.command_id,
		  scb->bus, scb->target_id, scb->lun);

	अगर ((scb->scsi_cmd) && (ips_is_passthru(scb->scsi_cmd)))
		/* passthru - just वापसs the raw result */
		वापस;

	errcode = DID_OK;

	अगर (((basic_status & IPS_GSC_STATUS_MASK) == IPS_CMD_SUCCESS) ||
	    ((basic_status & IPS_GSC_STATUS_MASK) == IPS_CMD_RECOVERED_ERROR)) अणु

		अगर (scb->bus == 0) अणु
			अगर ((basic_status & IPS_GSC_STATUS_MASK) ==
			    IPS_CMD_RECOVERED_ERROR) अणु
				DEBUG_VAR(1,
					  "(%s%d) Recovered Logical Drive Error OpCode: %x, BSB: %x, ESB: %x",
					  ips_name, ha->host_num,
					  scb->cmd.basic_io.op_code,
					  basic_status, ext_status);
			पूर्ण

			चयन (scb->scsi_cmd->cmnd[0]) अणु
			हाल ALLOW_MEDIUM_REMOVAL:
			हाल REZERO_UNIT:
			हाल ERASE:
			हाल WRITE_खाताMARKS:
			हाल SPACE:
				errcode = DID_ERROR;
				अवरोध;

			हाल START_STOP:
				अवरोध;

			हाल TEST_UNIT_READY:
				अगर (!ips_online(ha, scb)) अणु
					errcode = DID_TIME_OUT;
				पूर्ण
				अवरोध;

			हाल INQUIRY:
				अगर (ips_online(ha, scb)) अणु
					ips_inquiry(ha, scb);
				पूर्ण अन्यथा अणु
					errcode = DID_TIME_OUT;
				पूर्ण
				अवरोध;

			हाल REQUEST_SENSE:
				ips_reqsen(ha, scb);
				अवरोध;

			हाल READ_6:
			हाल WRITE_6:
			हाल READ_10:
			हाल WRITE_10:
			हाल RESERVE:
			हाल RELEASE:
				अवरोध;

			हाल MODE_SENSE:
				अगर (!ips_online(ha, scb)
				    || !ips_msense(ha, scb)) अणु
					errcode = DID_ERROR;
				पूर्ण
				अवरोध;

			हाल READ_CAPACITY:
				अगर (ips_online(ha, scb))
					ips_rdcap(ha, scb);
				अन्यथा अणु
					errcode = DID_TIME_OUT;
				पूर्ण
				अवरोध;

			हाल SEND_DIAGNOSTIC:
			हाल REASSIGN_BLOCKS:
				अवरोध;

			हाल FORMAT_UNIT:
				errcode = DID_ERROR;
				अवरोध;

			हाल SEEK_10:
			हाल VERIFY:
			हाल READ_DEFECT_DATA:
			हाल READ_BUFFER:
			हाल WRITE_BUFFER:
				अवरोध;

			शेष:
				errcode = DID_ERROR;
			पूर्ण	/* end चयन */

			scb->scsi_cmd->result = errcode << 16;
		पूर्ण अन्यथा अणु	/* bus == 0 */
			/* restrict access to physical drives */
			अगर (scb->scsi_cmd->cmnd[0] == INQUIRY) अणु
			    ips_scmd_buf_पढ़ो(scb->scsi_cmd,
                                  &inquiryData, माप (inquiryData));
			    अगर ((inquiryData.DeviceType & 0x1f) == TYPE_DISK)
			        scb->scsi_cmd->result = DID_TIME_OUT << 16;
			पूर्ण
		पूर्ण		/* अन्यथा */
	पूर्ण अन्यथा अणु		/* recovered error / success */
		अगर (scb->bus == 0) अणु
			DEBUG_VAR(1,
				  "(%s%d) Unrecovered Logical Drive Error OpCode: %x, BSB: %x, ESB: %x",
				  ips_name, ha->host_num,
				  scb->cmd.basic_io.op_code, basic_status,
				  ext_status);
		पूर्ण

		ips_map_status(ha, scb, sp);
	पूर्ण			/* अन्यथा */
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_online                                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Determine अगर a logical drive is online                                 */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_online(ips_ha_t * ha, ips_scb_t * scb)
अणु
	METHOD_TRACE("ips_online", 1);

	अगर (scb->target_id >= IPS_MAX_LD)
		वापस (0);

	अगर ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1) अणु
		स_रखो(ha->logical_drive_info, 0, माप (IPS_LD_INFO));
		वापस (0);
	पूर्ण

	अगर (ha->logical_drive_info->drive_info[scb->target_id].state !=
	    IPS_LD_OFFLINE
	    && ha->logical_drive_info->drive_info[scb->target_id].state !=
	    IPS_LD_FREE
	    && ha->logical_drive_info->drive_info[scb->target_id].state !=
	    IPS_LD_CRS
	    && ha->logical_drive_info->drive_info[scb->target_id].state !=
	    IPS_LD_SYS)
		वापस (1);
	अन्यथा
		वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_inquiry                                                */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Simulate an inquiry command to a logical drive                         */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_inquiry(ips_ha_t * ha, ips_scb_t * scb)
अणु
	IPS_SCSI_INQ_DATA inquiry;

	METHOD_TRACE("ips_inquiry", 1);

	स_रखो(&inquiry, 0, माप (IPS_SCSI_INQ_DATA));

	inquiry.DeviceType = IPS_SCSI_INQ_TYPE_DASD;
	inquiry.DeviceTypeQualअगरier = IPS_SCSI_INQ_LU_CONNECTED;
	inquiry.Version = IPS_SCSI_INQ_REV2;
	inquiry.ResponseDataFormat = IPS_SCSI_INQ_RD_REV2;
	inquiry.AdditionalLength = 31;
	inquiry.Flags[0] = IPS_SCSI_INQ_Address16;
	inquiry.Flags[1] =
	    IPS_SCSI_INQ_WBus16 | IPS_SCSI_INQ_Sync | IPS_SCSI_INQ_CmdQue;
	स_नकल(inquiry.VenकरोrId, "IBM     ", 8);
	स_नकल(inquiry.ProductId, "SERVERAID       ", 16);
	स_नकल(inquiry.ProductRevisionLevel, "1.00", 4);

	ips_scmd_buf_ग_लिखो(scb->scsi_cmd, &inquiry, माप (inquiry));

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_rdcap                                                  */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Simulate a पढ़ो capacity command to a logical drive                    */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_rdcap(ips_ha_t * ha, ips_scb_t * scb)
अणु
	IPS_SCSI_CAPACITY cap;

	METHOD_TRACE("ips_rdcap", 1);

	अगर (scsi_bufflen(scb->scsi_cmd) < 8)
		वापस (0);

	cap.lba =
	    cpu_to_be32(le32_to_cpu
			(ha->logical_drive_info->
			 drive_info[scb->target_id].sector_count) - 1);
	cap.len = cpu_to_be32((uपूर्णांक32_t) IPS_BLKSIZE);

	ips_scmd_buf_ग_लिखो(scb->scsi_cmd, &cap, माप (cap));

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_msense                                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Simulate a mode sense command to a logical drive                       */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_msense(ips_ha_t * ha, ips_scb_t * scb)
अणु
	uपूर्णांक16_t heads;
	uपूर्णांक16_t sectors;
	uपूर्णांक32_t cylinders;
	IPS_SCSI_MODE_PAGE_DATA mdata;

	METHOD_TRACE("ips_msense", 1);

	अगर (le32_to_cpu(ha->enq->ulDriveSize[scb->target_id]) > 0x400000 &&
	    (ha->enq->ucMiscFlag & 0x8) == 0) अणु
		heads = IPS_NORM_HEADS;
		sectors = IPS_NORM_SECTORS;
	पूर्ण अन्यथा अणु
		heads = IPS_COMP_HEADS;
		sectors = IPS_COMP_SECTORS;
	पूर्ण

	cylinders =
	    (le32_to_cpu(ha->enq->ulDriveSize[scb->target_id]) -
	     1) / (heads * sectors);

	स_रखो(&mdata, 0, माप (IPS_SCSI_MODE_PAGE_DATA));

	mdata.hdr.BlockDescLength = 8;

	चयन (scb->scsi_cmd->cmnd[2] & 0x3f) अणु
	हाल 0x03:		/* page 3 */
		mdata.pdata.pg3.PageCode = 3;
		mdata.pdata.pg3.PageLength = माप (IPS_SCSI_MODE_PAGE3);
		mdata.hdr.DataLength =
		    3 + mdata.hdr.BlockDescLength + mdata.pdata.pg3.PageLength;
		mdata.pdata.pg3.TracksPerZone = 0;
		mdata.pdata.pg3.AltSectorsPerZone = 0;
		mdata.pdata.pg3.AltTracksPerZone = 0;
		mdata.pdata.pg3.AltTracksPerVolume = 0;
		mdata.pdata.pg3.SectorsPerTrack = cpu_to_be16(sectors);
		mdata.pdata.pg3.BytesPerSector = cpu_to_be16(IPS_BLKSIZE);
		mdata.pdata.pg3.Interleave = cpu_to_be16(1);
		mdata.pdata.pg3.TrackSkew = 0;
		mdata.pdata.pg3.CylinderSkew = 0;
		mdata.pdata.pg3.flags = IPS_SCSI_MP3_SoftSector;
		अवरोध;

	हाल 0x4:
		mdata.pdata.pg4.PageCode = 4;
		mdata.pdata.pg4.PageLength = माप (IPS_SCSI_MODE_PAGE4);
		mdata.hdr.DataLength =
		    3 + mdata.hdr.BlockDescLength + mdata.pdata.pg4.PageLength;
		mdata.pdata.pg4.CylindersHigh =
		    cpu_to_be16((cylinders >> 8) & 0xFFFF);
		mdata.pdata.pg4.CylindersLow = (cylinders & 0xFF);
		mdata.pdata.pg4.Heads = heads;
		mdata.pdata.pg4.WritePrecompHigh = 0;
		mdata.pdata.pg4.WritePrecompLow = 0;
		mdata.pdata.pg4.ReducedWriteCurrentHigh = 0;
		mdata.pdata.pg4.ReducedWriteCurrentLow = 0;
		mdata.pdata.pg4.StepRate = cpu_to_be16(1);
		mdata.pdata.pg4.LandingZoneHigh = 0;
		mdata.pdata.pg4.LandingZoneLow = 0;
		mdata.pdata.pg4.flags = 0;
		mdata.pdata.pg4.RotationalOffset = 0;
		mdata.pdata.pg4.MediumRotationRate = 0;
		अवरोध;
	हाल 0x8:
		mdata.pdata.pg8.PageCode = 8;
		mdata.pdata.pg8.PageLength = माप (IPS_SCSI_MODE_PAGE8);
		mdata.hdr.DataLength =
		    3 + mdata.hdr.BlockDescLength + mdata.pdata.pg8.PageLength;
		/* everything अन्यथा is left set to 0 */
		अवरोध;

	शेष:
		वापस (0);
	पूर्ण			/* end चयन */

	ips_scmd_buf_ग_लिखो(scb->scsi_cmd, &mdata, माप (mdata));

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_reqsen                                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Simulate a request sense command to a logical drive                    */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_reqsen(ips_ha_t * ha, ips_scb_t * scb)
अणु
	IPS_SCSI_REQSEN reqsen;

	METHOD_TRACE("ips_reqsen", 1);

	स_रखो(&reqsen, 0, माप (IPS_SCSI_REQSEN));

	reqsen.ResponseCode =
	    IPS_SCSI_REQSEN_VALID | IPS_SCSI_REQSEN_CURRENT_ERR;
	reqsen.AdditionalLength = 10;
	reqsen.AdditionalSenseCode = IPS_SCSI_REQSEN_NO_SENSE;
	reqsen.AdditionalSenseCodeQual = IPS_SCSI_REQSEN_NO_SENSE;

	ips_scmd_buf_ग_लिखो(scb->scsi_cmd, &reqsen, माप (reqsen));

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_मुक्त                                                   */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Free any allocated space क्रम this controller                           */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_मुक्त(ips_ha_t * ha)
अणु

	METHOD_TRACE("ips_free", 1);

	अगर (ha) अणु
		अगर (ha->enq) अणु
			dma_मुक्त_coherent(&ha->pcidev->dev, माप(IPS_ENQ),
					    ha->enq, ha->enq_busaddr);
			ha->enq = शून्य;
		पूर्ण

		kमुक्त(ha->conf);
		ha->conf = शून्य;

		अगर (ha->adapt) अणु
			dma_मुक्त_coherent(&ha->pcidev->dev,
					    माप (IPS_ADAPTER) +
					    माप (IPS_IO_CMD), ha->adapt,
					    ha->adapt->hw_status_start);
			ha->adapt = शून्य;
		पूर्ण

		अगर (ha->logical_drive_info) अणु
			dma_मुक्त_coherent(&ha->pcidev->dev,
					    माप (IPS_LD_INFO),
					    ha->logical_drive_info,
					    ha->logical_drive_info_dma_addr);
			ha->logical_drive_info = शून्य;
		पूर्ण

		kमुक्त(ha->nvram);
		ha->nvram = शून्य;

		kमुक्त(ha->subsys);
		ha->subsys = शून्य;

		अगर (ha->ioctl_data) अणु
			dma_मुक्त_coherent(&ha->pcidev->dev, ha->ioctl_len,
					    ha->ioctl_data, ha->ioctl_busaddr);
			ha->ioctl_data = शून्य;
			ha->ioctl_datasize = 0;
			ha->ioctl_len = 0;
		पूर्ण
		ips_deallocatescbs(ha, ha->max_cmds);

		/* मुक्त memory mapped (अगर applicable) */
		अगर (ha->mem_ptr) अणु
			iounmap(ha->ioremap_ptr);
			ha->ioremap_ptr = शून्य;
			ha->mem_ptr = शून्य;
		पूर्ण

		ha->mem_addr = 0;

	पूर्ण
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_deallocatescbs                                         */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Free the command blocks                                                */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_deallocatescbs(ips_ha_t * ha, पूर्णांक cmds)
अणु
	अगर (ha->scbs) अणु
		dma_मुक्त_coherent(&ha->pcidev->dev,
				    IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * cmds,
				    ha->scbs->sg_list.list,
				    ha->scbs->sg_busaddr);
		dma_मुक्त_coherent(&ha->pcidev->dev, माप (ips_scb_t) * cmds,
				    ha->scbs, ha->scbs->scb_busaddr);
		ha->scbs = शून्य;
	पूर्ण			/* end अगर */
	वापस 1;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_allocatescbs                                           */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Allocate the command blocks                                            */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_allocatescbs(ips_ha_t * ha)
अणु
	ips_scb_t *scb_p;
	IPS_SG_LIST ips_sg;
	पूर्णांक i;
	dma_addr_t command_dma, sg_dma;

	METHOD_TRACE("ips_allocatescbs", 1);

	/* Allocate memory क्रम the SCBs */
	ha->scbs = dma_alloc_coherent(&ha->pcidev->dev,
			ha->max_cmds * माप (ips_scb_t),
			&command_dma, GFP_KERNEL);
	अगर (ha->scbs == शून्य)
		वापस 0;
	ips_sg.list = dma_alloc_coherent(&ha->pcidev->dev,
			IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * ha->max_cmds,
			&sg_dma, GFP_KERNEL);
	अगर (ips_sg.list == शून्य) अणु
		dma_मुक्त_coherent(&ha->pcidev->dev,
				    ha->max_cmds * माप (ips_scb_t), ha->scbs,
				    command_dma);
		वापस 0;
	पूर्ण

	स_रखो(ha->scbs, 0, ha->max_cmds * माप (ips_scb_t));

	क्रम (i = 0; i < ha->max_cmds; i++) अणु
		scb_p = &ha->scbs[i];
		scb_p->scb_busaddr = command_dma + माप (ips_scb_t) * i;
		/* set up S/G list */
		अगर (IPS_USE_ENH_SGLIST(ha)) अणु
			scb_p->sg_list.enh_list =
			    ips_sg.enh_list + i * IPS_MAX_SG;
			scb_p->sg_busaddr =
			    sg_dma + IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * i;
		पूर्ण अन्यथा अणु
			scb_p->sg_list.std_list =
			    ips_sg.std_list + i * IPS_MAX_SG;
			scb_p->sg_busaddr =
			    sg_dma + IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * i;
		पूर्ण

		/* add to the मुक्त list */
		अगर (i < ha->max_cmds - 1) अणु
			scb_p->q_next = ha->scb_मुक्तlist;
			ha->scb_मुक्तlist = scb_p;
		पूर्ण
	पूर्ण

	/* success */
	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_init_scb                                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize a CCB to शेष values                                     */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_init_scb(ips_ha_t * ha, ips_scb_t * scb)
अणु
	IPS_SG_LIST sg_list;
	uपूर्णांक32_t cmd_busaddr, sg_busaddr;
	METHOD_TRACE("ips_init_scb", 1);

	अगर (scb == शून्य)
		वापस;

	sg_list.list = scb->sg_list.list;
	cmd_busaddr = scb->scb_busaddr;
	sg_busaddr = scb->sg_busaddr;
	/* zero fill */
	स_रखो(scb, 0, माप (ips_scb_t));
	स_रखो(ha->dummy, 0, माप (IPS_IO_CMD));

	/* Initialize dummy command bucket */
	ha->dummy->op_code = 0xFF;
	ha->dummy->ccsar = cpu_to_le32(ha->adapt->hw_status_start
				       + माप (IPS_ADAPTER));
	ha->dummy->command_id = IPS_MAX_CMDS;

	/* set bus address of scb */
	scb->scb_busaddr = cmd_busaddr;
	scb->sg_busaddr = sg_busaddr;
	scb->sg_list.list = sg_list.list;

	/* Neptune Fix */
	scb->cmd.basic_io.cccr = cpu_to_le32((uपूर्णांक32_t) IPS_BIT_ILE);
	scb->cmd.basic_io.ccsar = cpu_to_le32(ha->adapt->hw_status_start
					      + माप (IPS_ADAPTER));
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_get_scb                                                */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize a CCB to शेष values                                     */
/*                                                                          */
/* ASSUMED to be called from within a lock                                 */
/*                                                                          */
/****************************************************************************/
अटल ips_scb_t *
ips_माला_लोcb(ips_ha_t * ha)
अणु
	ips_scb_t *scb;

	METHOD_TRACE("ips_getscb", 1);

	अगर ((scb = ha->scb_मुक्तlist) == शून्य) अणु

		वापस (शून्य);
	पूर्ण

	ha->scb_मुक्तlist = scb->q_next;
	scb->flags = 0;
	scb->q_next = शून्य;

	ips_init_scb(ha, scb);

	वापस (scb);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_मुक्त_scb                                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Return an unused CCB back to the मुक्त list                             */
/*                                                                          */
/* ASSUMED to be called from within a lock                                  */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_मुक्तscb(ips_ha_t * ha, ips_scb_t * scb)
अणु

	METHOD_TRACE("ips_freescb", 1);
	अगर (scb->flags & IPS_SCB_MAP_SG)
                scsi_dma_unmap(scb->scsi_cmd);
	अन्यथा अगर (scb->flags & IPS_SCB_MAP_SINGLE)
		dma_unmap_single(&ha->pcidev->dev, scb->data_busaddr,
				 scb->data_len, IPS_DMA_सूची(scb));

	/* check to make sure this is not our "special" scb */
	अगर (IPS_COMMAND_ID(ha, scb) < (ha->max_cmds - 1)) अणु
		scb->q_next = ha->scb_मुक्तlist;
		ha->scb_मुक्तlist = scb;
	पूर्ण
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_isinit_copperhead                                      */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Is controller initialized ?                                            */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_isinit_copperhead(ips_ha_t * ha)
अणु
	uपूर्णांक8_t scpr;
	uपूर्णांक8_t isr;

	METHOD_TRACE("ips_isinit_copperhead", 1);

	isr = inb(ha->io_addr + IPS_REG_HISR);
	scpr = inb(ha->io_addr + IPS_REG_SCPR);

	अगर (((isr & IPS_BIT_EI) == 0) && ((scpr & IPS_BIT_EBM) == 0))
		वापस (0);
	अन्यथा
		वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_isinit_copperhead_memio                                */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Is controller initialized ?                                            */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_isinit_copperhead_memio(ips_ha_t * ha)
अणु
	uपूर्णांक8_t isr = 0;
	uपूर्णांक8_t scpr;

	METHOD_TRACE("ips_is_init_copperhead_memio", 1);

	isr = पढ़ोb(ha->mem_ptr + IPS_REG_HISR);
	scpr = पढ़ोb(ha->mem_ptr + IPS_REG_SCPR);

	अगर (((isr & IPS_BIT_EI) == 0) && ((scpr & IPS_BIT_EBM) == 0))
		वापस (0);
	अन्यथा
		वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_isinit_morpheus                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Is controller initialized ?                                            */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_isinit_morpheus(ips_ha_t * ha)
अणु
	uपूर्णांक32_t post;
	uपूर्णांक32_t bits;

	METHOD_TRACE("ips_is_init_morpheus", 1);

	अगर (ips_isपूर्णांकr_morpheus(ha))
	    ips_flush_and_reset(ha);

	post = पढ़ोl(ha->mem_ptr + IPS_REG_I960_MSG0);
	bits = पढ़ोl(ha->mem_ptr + IPS_REG_I2O_HIR);

	अगर (post == 0)
		वापस (0);
	अन्यथा अगर (bits & 0x3)
		वापस (0);
	अन्यथा
		वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_flush_and_reset                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Perक्रमm cleanup ( FLUSH and RESET ) when the adapter is in an unknown  */
/*   state ( was trying to INIT and an पूर्णांकerrupt was alपढ़ोy pending ) ...  */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_flush_and_reset(ips_ha_t *ha)
अणु
	ips_scb_t *scb;
	पूर्णांक  ret;
 	पूर्णांक  समय;
	पूर्णांक  करोne;
	dma_addr_t command_dma;

	/* Create a usuable SCB */
	scb = dma_alloc_coherent(&ha->pcidev->dev, माप(ips_scb_t),
			&command_dma, GFP_KERNEL);
	अगर (scb) अणु
	    स_रखो(scb, 0, माप(ips_scb_t));
	    ips_init_scb(ha, scb);
	    scb->scb_busaddr = command_dma;

	    scb->समयout = ips_cmd_समयout;
	    scb->cdb[0] = IPS_CMD_FLUSH;

	    scb->cmd.flush_cache.op_code = IPS_CMD_FLUSH;
	    scb->cmd.flush_cache.command_id = IPS_MAX_CMDS;   /* Use an ID that would otherwise not exist */
	    scb->cmd.flush_cache.state = IPS_NORM_STATE;
	    scb->cmd.flush_cache.reserved = 0;
	    scb->cmd.flush_cache.reserved2 = 0;
	    scb->cmd.flush_cache.reserved3 = 0;
	    scb->cmd.flush_cache.reserved4 = 0;

	    ret = ips_send_cmd(ha, scb);                      /* Send the Flush Command */

	    अगर (ret == IPS_SUCCESS) अणु
	        समय = 60 * IPS_ONE_SEC;	              /* Max Wait समय is 60 seconds */
	        करोne = 0;

	        जबतक ((समय > 0) && (!करोne)) अणु
		   करोne = ips_poll_क्रम_flush_complete(ha);
	           /* This may look evil, but it's only करोne during extremely rare start-up conditions ! */
	           udelay(1000);
	           समय--;
	        पूर्ण
        पूर्ण
	पूर्ण

	/* Now RESET and INIT the adapter */
	(*ha->func.reset) (ha);

	dma_मुक्त_coherent(&ha->pcidev->dev, माप(ips_scb_t), scb, command_dma);
	वापस;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_poll_क्रम_flush_complete                                */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Poll क्रम the Flush Command issued by ips_flush_and_reset() to complete */
/*   All other responses are just taken off the queue and ignored           */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_poll_क्रम_flush_complete(ips_ha_t * ha)
अणु
	IPS_STATUS cstatus;

	जबतक (TRUE) अणु
	    cstatus.value = (*ha->func.statupd) (ha);

	    अगर (cstatus.value == 0xffffffff)      /* If No Interrupt to process */
			अवरोध;

	    /* Success is when we see the Flush Command ID */
	    अगर (cstatus.fields.command_id == IPS_MAX_CMDS)
	        वापस 1;
	 पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_enable_पूर्णांक_copperhead                                  */
/*                                                                          */
/* Routine Description:                                                     */
/*   Turn on पूर्णांकerrupts                                                     */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_enable_पूर्णांक_copperhead(ips_ha_t * ha)
अणु
	METHOD_TRACE("ips_enable_int_copperhead", 1);

	outb(ha->io_addr + IPS_REG_HISR, IPS_BIT_EI);
	inb(ha->io_addr + IPS_REG_HISR);	/*Ensure PCI Posting Completes*/
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_enable_पूर्णांक_copperhead_memio                            */
/*                                                                          */
/* Routine Description:                                                     */
/*   Turn on पूर्णांकerrupts                                                     */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_enable_पूर्णांक_copperhead_memio(ips_ha_t * ha)
अणु
	METHOD_TRACE("ips_enable_int_copperhead_memio", 1);

	ग_लिखोb(IPS_BIT_EI, ha->mem_ptr + IPS_REG_HISR);
	पढ़ोb(ha->mem_ptr + IPS_REG_HISR);	/*Ensure PCI Posting Completes*/
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_enable_पूर्णांक_morpheus                                    */
/*                                                                          */
/* Routine Description:                                                     */
/*   Turn on पूर्णांकerrupts                                                     */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_enable_पूर्णांक_morpheus(ips_ha_t * ha)
अणु
	uपूर्णांक32_t Oimr;

	METHOD_TRACE("ips_enable_int_morpheus", 1);

	Oimr = पढ़ोl(ha->mem_ptr + IPS_REG_I960_OIMR);
	Oimr &= ~0x08;
	ग_लिखोl(Oimr, ha->mem_ptr + IPS_REG_I960_OIMR);
	पढ़ोl(ha->mem_ptr + IPS_REG_I960_OIMR);	/*Ensure PCI Posting Completes*/
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_init_copperhead                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize a copperhead controller                                     */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_init_copperhead(ips_ha_t * ha)
अणु
	uपूर्णांक8_t Isr;
	uपूर्णांक8_t Cbsp;
	uपूर्णांक8_t PostByte[IPS_MAX_POST_BYTES];
	पूर्णांक i, j;

	METHOD_TRACE("ips_init_copperhead", 1);

	क्रम (i = 0; i < IPS_MAX_POST_BYTES; i++) अणु
		क्रम (j = 0; j < 45; j++) अणु
			Isr = inb(ha->io_addr + IPS_REG_HISR);
			अगर (Isr & IPS_BIT_GHI)
				अवरोध;

			/* Delay क्रम 1 Second */
			MDELAY(IPS_ONE_SEC);
		पूर्ण

		अगर (j >= 45)
			/* error occurred */
			वापस (0);

		PostByte[i] = inb(ha->io_addr + IPS_REG_ISPR);
		outb(Isr, ha->io_addr + IPS_REG_HISR);
	पूर्ण

	अगर (PostByte[0] < IPS_GOOD_POST_STATUS) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "reset controller fails (post status %x %x).\n",
			   PostByte[0], PostByte[1]);

		वापस (0);
	पूर्ण

	क्रम (i = 0; i < IPS_MAX_CONFIG_BYTES; i++) अणु
		क्रम (j = 0; j < 240; j++) अणु
			Isr = inb(ha->io_addr + IPS_REG_HISR);
			अगर (Isr & IPS_BIT_GHI)
				अवरोध;

			/* Delay क्रम 1 Second */
			MDELAY(IPS_ONE_SEC);
		पूर्ण

		अगर (j >= 240)
			/* error occurred */
			वापस (0);

		inb(ha->io_addr + IPS_REG_ISPR);
		outb(Isr, ha->io_addr + IPS_REG_HISR);
	पूर्ण

	क्रम (i = 0; i < 240; i++) अणु
		Cbsp = inb(ha->io_addr + IPS_REG_CBSP);

		अगर ((Cbsp & IPS_BIT_OP) == 0)
			अवरोध;

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);
	पूर्ण

	अगर (i >= 240)
		/* reset failed */
		वापस (0);

	/* setup CCCR */
	outl(0x1010, ha->io_addr + IPS_REG_CCCR);

	/* Enable busmastering */
	outb(IPS_BIT_EBM, ha->io_addr + IPS_REG_SCPR);

	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		/* fix क्रम anaconda64 */
		outl(0, ha->io_addr + IPS_REG_NDAE);

	/* Enable पूर्णांकerrupts */
	outb(IPS_BIT_EI, ha->io_addr + IPS_REG_HISR);

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_init_copperhead_memio                                  */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize a copperhead controller with memory mapped I/O              */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_init_copperhead_memio(ips_ha_t * ha)
अणु
	uपूर्णांक8_t Isr = 0;
	uपूर्णांक8_t Cbsp;
	uपूर्णांक8_t PostByte[IPS_MAX_POST_BYTES];
	पूर्णांक i, j;

	METHOD_TRACE("ips_init_copperhead_memio", 1);

	क्रम (i = 0; i < IPS_MAX_POST_BYTES; i++) अणु
		क्रम (j = 0; j < 45; j++) अणु
			Isr = पढ़ोb(ha->mem_ptr + IPS_REG_HISR);
			अगर (Isr & IPS_BIT_GHI)
				अवरोध;

			/* Delay क्रम 1 Second */
			MDELAY(IPS_ONE_SEC);
		पूर्ण

		अगर (j >= 45)
			/* error occurred */
			वापस (0);

		PostByte[i] = पढ़ोb(ha->mem_ptr + IPS_REG_ISPR);
		ग_लिखोb(Isr, ha->mem_ptr + IPS_REG_HISR);
	पूर्ण

	अगर (PostByte[0] < IPS_GOOD_POST_STATUS) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "reset controller fails (post status %x %x).\n",
			   PostByte[0], PostByte[1]);

		वापस (0);
	पूर्ण

	क्रम (i = 0; i < IPS_MAX_CONFIG_BYTES; i++) अणु
		क्रम (j = 0; j < 240; j++) अणु
			Isr = पढ़ोb(ha->mem_ptr + IPS_REG_HISR);
			अगर (Isr & IPS_BIT_GHI)
				अवरोध;

			/* Delay क्रम 1 Second */
			MDELAY(IPS_ONE_SEC);
		पूर्ण

		अगर (j >= 240)
			/* error occurred */
			वापस (0);

		पढ़ोb(ha->mem_ptr + IPS_REG_ISPR);
		ग_लिखोb(Isr, ha->mem_ptr + IPS_REG_HISR);
	पूर्ण

	क्रम (i = 0; i < 240; i++) अणु
		Cbsp = पढ़ोb(ha->mem_ptr + IPS_REG_CBSP);

		अगर ((Cbsp & IPS_BIT_OP) == 0)
			अवरोध;

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);
	पूर्ण

	अगर (i >= 240)
		/* error occurred */
		वापस (0);

	/* setup CCCR */
	ग_लिखोl(0x1010, ha->mem_ptr + IPS_REG_CCCR);

	/* Enable busmastering */
	ग_लिखोb(IPS_BIT_EBM, ha->mem_ptr + IPS_REG_SCPR);

	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		/* fix क्रम anaconda64 */
		ग_लिखोl(0, ha->mem_ptr + IPS_REG_NDAE);

	/* Enable पूर्णांकerrupts */
	ग_लिखोb(IPS_BIT_EI, ha->mem_ptr + IPS_REG_HISR);

	/* अगर we get here then everything went OK */
	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_init_morpheus                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize a morpheus controller                                       */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_init_morpheus(ips_ha_t * ha)
अणु
	uपूर्णांक32_t Post;
	uपूर्णांक32_t Config;
	uपूर्णांक32_t Isr;
	uपूर्णांक32_t Oimr;
	पूर्णांक i;

	METHOD_TRACE("ips_init_morpheus", 1);

	/* Wait up to 45 secs क्रम Post */
	क्रम (i = 0; i < 45; i++) अणु
		Isr = पढ़ोl(ha->mem_ptr + IPS_REG_I2O_HIR);

		अगर (Isr & IPS_BIT_I960_MSG0I)
			अवरोध;

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);
	पूर्ण

	अगर (i >= 45) अणु
		/* error occurred */
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "timeout waiting for post.\n");

		वापस (0);
	पूर्ण

	Post = पढ़ोl(ha->mem_ptr + IPS_REG_I960_MSG0);

	अगर (Post == 0x4F00) अणु	/* If Flashing the Battery PIC         */
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Flashing Battery PIC, Please wait ...\n");

		/* Clear the पूर्णांकerrupt bit */
		Isr = (uपूर्णांक32_t) IPS_BIT_I960_MSG0I;
		ग_लिखोl(Isr, ha->mem_ptr + IPS_REG_I2O_HIR);

		क्रम (i = 0; i < 120; i++) अणु	/*    Wait Up to 2 Min. क्रम Completion */
			Post = पढ़ोl(ha->mem_ptr + IPS_REG_I960_MSG0);
			अगर (Post != 0x4F00)
				अवरोध;
			/* Delay क्रम 1 Second */
			MDELAY(IPS_ONE_SEC);
		पूर्ण

		अगर (i >= 120) अणु
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "timeout waiting for Battery PIC Flash\n");
			वापस (0);
		पूर्ण

	पूर्ण

	/* Clear the पूर्णांकerrupt bit */
	Isr = (uपूर्णांक32_t) IPS_BIT_I960_MSG0I;
	ग_लिखोl(Isr, ha->mem_ptr + IPS_REG_I2O_HIR);

	अगर (Post < (IPS_GOOD_POST_STATUS << 8)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "reset controller fails (post status %x).\n", Post);

		वापस (0);
	पूर्ण

	/* Wait up to 240 secs क्रम config bytes */
	क्रम (i = 0; i < 240; i++) अणु
		Isr = पढ़ोl(ha->mem_ptr + IPS_REG_I2O_HIR);

		अगर (Isr & IPS_BIT_I960_MSG1I)
			अवरोध;

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);
	पूर्ण

	अगर (i >= 240) अणु
		/* error occurred */
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "timeout waiting for config.\n");

		वापस (0);
	पूर्ण

	Config = पढ़ोl(ha->mem_ptr + IPS_REG_I960_MSG1);

	/* Clear पूर्णांकerrupt bit */
	Isr = (uपूर्णांक32_t) IPS_BIT_I960_MSG1I;
	ग_लिखोl(Isr, ha->mem_ptr + IPS_REG_I2O_HIR);

	/* Turn on the पूर्णांकerrupts */
	Oimr = पढ़ोl(ha->mem_ptr + IPS_REG_I960_OIMR);
	Oimr &= ~0x8;
	ग_लिखोl(Oimr, ha->mem_ptr + IPS_REG_I960_OIMR);

	/* अगर we get here then everything went OK */

	/* Since we did a RESET, an EraseStripeLock may be needed */
	अगर (Post == 0xEF10) अणु
		अगर ((Config == 0x000F) || (Config == 0x0009))
			ha->requires_esl = 1;
	पूर्ण

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_reset_copperhead                                       */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Reset the controller                                                   */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_reset_copperhead(ips_ha_t * ha)
अणु
	पूर्णांक reset_counter;

	METHOD_TRACE("ips_reset_copperhead", 1);

	DEBUG_VAR(1, "(%s%d) ips_reset_copperhead: io addr: %x, irq: %d",
		  ips_name, ha->host_num, ha->io_addr, ha->pcidev->irq);

	reset_counter = 0;

	जबतक (reset_counter < 2) अणु
		reset_counter++;

		outb(IPS_BIT_RST, ha->io_addr + IPS_REG_SCPR);

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);

		outb(0, ha->io_addr + IPS_REG_SCPR);

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);

		अगर ((*ha->func.init) (ha))
			अवरोध;
		अन्यथा अगर (reset_counter >= 2) अणु

			वापस (0);
		पूर्ण
	पूर्ण

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_reset_copperhead_memio                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Reset the controller                                                   */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_reset_copperhead_memio(ips_ha_t * ha)
अणु
	पूर्णांक reset_counter;

	METHOD_TRACE("ips_reset_copperhead_memio", 1);

	DEBUG_VAR(1, "(%s%d) ips_reset_copperhead_memio: mem addr: %x, irq: %d",
		  ips_name, ha->host_num, ha->mem_addr, ha->pcidev->irq);

	reset_counter = 0;

	जबतक (reset_counter < 2) अणु
		reset_counter++;

		ग_लिखोb(IPS_BIT_RST, ha->mem_ptr + IPS_REG_SCPR);

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);

		ग_लिखोb(0, ha->mem_ptr + IPS_REG_SCPR);

		/* Delay क्रम 1 Second */
		MDELAY(IPS_ONE_SEC);

		अगर ((*ha->func.init) (ha))
			अवरोध;
		अन्यथा अगर (reset_counter >= 2) अणु

			वापस (0);
		पूर्ण
	पूर्ण

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_reset_morpheus                                         */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Reset the controller                                                   */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_reset_morpheus(ips_ha_t * ha)
अणु
	पूर्णांक reset_counter;
	uपूर्णांक8_t junk;

	METHOD_TRACE("ips_reset_morpheus", 1);

	DEBUG_VAR(1, "(%s%d) ips_reset_morpheus: mem addr: %x, irq: %d",
		  ips_name, ha->host_num, ha->mem_addr, ha->pcidev->irq);

	reset_counter = 0;

	जबतक (reset_counter < 2) अणु
		reset_counter++;

		ग_लिखोl(0x80000000, ha->mem_ptr + IPS_REG_I960_IDR);

		/* Delay क्रम 5 Seconds */
		MDELAY(5 * IPS_ONE_SEC);

		/* Do a PCI config पढ़ो to रुको क्रम adapter */
		pci_पढ़ो_config_byte(ha->pcidev, 4, &junk);

		अगर ((*ha->func.init) (ha))
			अवरोध;
		अन्यथा अगर (reset_counter >= 2) अणु

			वापस (0);
		पूर्ण
	पूर्ण

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_statinit                                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize the status queues on the controller                         */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_statinit(ips_ha_t * ha)
अणु
	uपूर्णांक32_t phys_status_start;

	METHOD_TRACE("ips_statinit", 1);

	ha->adapt->p_status_start = ha->adapt->status;
	ha->adapt->p_status_end = ha->adapt->status + IPS_MAX_CMDS;
	ha->adapt->p_status_tail = ha->adapt->status;

	phys_status_start = ha->adapt->hw_status_start;
	outl(phys_status_start, ha->io_addr + IPS_REG_SQSR);
	outl(phys_status_start + IPS_STATUS_Q_SIZE,
	     ha->io_addr + IPS_REG_SQER);
	outl(phys_status_start + IPS_STATUS_SIZE,
	     ha->io_addr + IPS_REG_SQHR);
	outl(phys_status_start, ha->io_addr + IPS_REG_SQTR);

	ha->adapt->hw_status_tail = phys_status_start;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_statinit_memio                                         */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Initialize the status queues on the controller                         */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_statinit_memio(ips_ha_t * ha)
अणु
	uपूर्णांक32_t phys_status_start;

	METHOD_TRACE("ips_statinit_memio", 1);

	ha->adapt->p_status_start = ha->adapt->status;
	ha->adapt->p_status_end = ha->adapt->status + IPS_MAX_CMDS;
	ha->adapt->p_status_tail = ha->adapt->status;

	phys_status_start = ha->adapt->hw_status_start;
	ग_लिखोl(phys_status_start, ha->mem_ptr + IPS_REG_SQSR);
	ग_लिखोl(phys_status_start + IPS_STATUS_Q_SIZE,
	       ha->mem_ptr + IPS_REG_SQER);
	ग_लिखोl(phys_status_start + IPS_STATUS_SIZE, ha->mem_ptr + IPS_REG_SQHR);
	ग_लिखोl(phys_status_start, ha->mem_ptr + IPS_REG_SQTR);

	ha->adapt->hw_status_tail = phys_status_start;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_statupd_copperhead                                     */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove an element from the status queue                                */
/*                                                                          */
/****************************************************************************/
अटल uपूर्णांक32_t
ips_statupd_copperhead(ips_ha_t * ha)
अणु
	METHOD_TRACE("ips_statupd_copperhead", 1);

	अगर (ha->adapt->p_status_tail != ha->adapt->p_status_end) अणु
		ha->adapt->p_status_tail++;
		ha->adapt->hw_status_tail += माप (IPS_STATUS);
	पूर्ण अन्यथा अणु
		ha->adapt->p_status_tail = ha->adapt->p_status_start;
		ha->adapt->hw_status_tail = ha->adapt->hw_status_start;
	पूर्ण

	outl(ha->adapt->hw_status_tail,
	     ha->io_addr + IPS_REG_SQTR);

	वापस (ha->adapt->p_status_tail->value);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_statupd_copperhead_memio                               */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove an element from the status queue                                */
/*                                                                          */
/****************************************************************************/
अटल uपूर्णांक32_t
ips_statupd_copperhead_memio(ips_ha_t * ha)
अणु
	METHOD_TRACE("ips_statupd_copperhead_memio", 1);

	अगर (ha->adapt->p_status_tail != ha->adapt->p_status_end) अणु
		ha->adapt->p_status_tail++;
		ha->adapt->hw_status_tail += माप (IPS_STATUS);
	पूर्ण अन्यथा अणु
		ha->adapt->p_status_tail = ha->adapt->p_status_start;
		ha->adapt->hw_status_tail = ha->adapt->hw_status_start;
	पूर्ण

	ग_लिखोl(ha->adapt->hw_status_tail, ha->mem_ptr + IPS_REG_SQTR);

	वापस (ha->adapt->p_status_tail->value);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_statupd_morpheus                                       */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Remove an element from the status queue                                */
/*                                                                          */
/****************************************************************************/
अटल uपूर्णांक32_t
ips_statupd_morpheus(ips_ha_t * ha)
अणु
	uपूर्णांक32_t val;

	METHOD_TRACE("ips_statupd_morpheus", 1);

	val = पढ़ोl(ha->mem_ptr + IPS_REG_I2O_OUTMSGQ);

	वापस (val);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_issue_copperhead                                       */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Send a command करोwn to the controller                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_issue_copperhead(ips_ha_t * ha, ips_scb_t * scb)
अणु
	uपूर्णांक32_t TimeOut;
	uपूर्णांक32_t val;

	METHOD_TRACE("ips_issue_copperhead", 1);

	अगर (scb->scsi_cmd) अणु
		DEBUG_VAR(2, "(%s%d) ips_issue: cmd 0x%X id %d (%d %d %d)",
			  ips_name,
			  ha->host_num,
			  scb->cdb[0],
			  scb->cmd.basic_io.command_id,
			  scb->bus, scb->target_id, scb->lun);
	पूर्ण अन्यथा अणु
		DEBUG_VAR(2, KERN_NOTICE "(%s%d) ips_issue: logical cmd id %d",
			  ips_name, ha->host_num, scb->cmd.basic_io.command_id);
	पूर्ण

	TimeOut = 0;

	जबतक ((val =
		le32_to_cpu(inl(ha->io_addr + IPS_REG_CCCR))) & IPS_BIT_SEM) अणु
		udelay(1000);

		अगर (++TimeOut >= IPS_SEM_TIMEOUT) अणु
			अगर (!(val & IPS_BIT_START_STOP))
				अवरोध;

			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "ips_issue val [0x%x].\n", val);
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "ips_issue semaphore chk timeout.\n");

			वापस (IPS_FAILURE);
		पूर्ण		/* end अगर */
	पूर्ण			/* end जबतक */

	outl(scb->scb_busaddr, ha->io_addr + IPS_REG_CCSAR);
	outw(IPS_BIT_START_CMD, ha->io_addr + IPS_REG_CCCR);

	वापस (IPS_SUCCESS);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_issue_copperhead_memio                                 */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Send a command करोwn to the controller                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_issue_copperhead_memio(ips_ha_t * ha, ips_scb_t * scb)
अणु
	uपूर्णांक32_t TimeOut;
	uपूर्णांक32_t val;

	METHOD_TRACE("ips_issue_copperhead_memio", 1);

	अगर (scb->scsi_cmd) अणु
		DEBUG_VAR(2, "(%s%d) ips_issue: cmd 0x%X id %d (%d %d %d)",
			  ips_name,
			  ha->host_num,
			  scb->cdb[0],
			  scb->cmd.basic_io.command_id,
			  scb->bus, scb->target_id, scb->lun);
	पूर्ण अन्यथा अणु
		DEBUG_VAR(2, "(%s%d) ips_issue: logical cmd id %d",
			  ips_name, ha->host_num, scb->cmd.basic_io.command_id);
	पूर्ण

	TimeOut = 0;

	जबतक ((val = पढ़ोl(ha->mem_ptr + IPS_REG_CCCR)) & IPS_BIT_SEM) अणु
		udelay(1000);

		अगर (++TimeOut >= IPS_SEM_TIMEOUT) अणु
			अगर (!(val & IPS_BIT_START_STOP))
				अवरोध;

			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "ips_issue val [0x%x].\n", val);
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "ips_issue semaphore chk timeout.\n");

			वापस (IPS_FAILURE);
		पूर्ण		/* end अगर */
	पूर्ण			/* end जबतक */

	ग_लिखोl(scb->scb_busaddr, ha->mem_ptr + IPS_REG_CCSAR);
	ग_लिखोl(IPS_BIT_START_CMD, ha->mem_ptr + IPS_REG_CCCR);

	वापस (IPS_SUCCESS);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_issue_i2o                                              */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Send a command करोwn to the controller                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_issue_i2o(ips_ha_t * ha, ips_scb_t * scb)
अणु

	METHOD_TRACE("ips_issue_i2o", 1);

	अगर (scb->scsi_cmd) अणु
		DEBUG_VAR(2, "(%s%d) ips_issue: cmd 0x%X id %d (%d %d %d)",
			  ips_name,
			  ha->host_num,
			  scb->cdb[0],
			  scb->cmd.basic_io.command_id,
			  scb->bus, scb->target_id, scb->lun);
	पूर्ण अन्यथा अणु
		DEBUG_VAR(2, "(%s%d) ips_issue: logical cmd id %d",
			  ips_name, ha->host_num, scb->cmd.basic_io.command_id);
	पूर्ण

	outl(scb->scb_busaddr, ha->io_addr + IPS_REG_I2O_INMSGQ);

	वापस (IPS_SUCCESS);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_issue_i2o_memio                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Send a command करोwn to the controller                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_issue_i2o_memio(ips_ha_t * ha, ips_scb_t * scb)
अणु

	METHOD_TRACE("ips_issue_i2o_memio", 1);

	अगर (scb->scsi_cmd) अणु
		DEBUG_VAR(2, "(%s%d) ips_issue: cmd 0x%X id %d (%d %d %d)",
			  ips_name,
			  ha->host_num,
			  scb->cdb[0],
			  scb->cmd.basic_io.command_id,
			  scb->bus, scb->target_id, scb->lun);
	पूर्ण अन्यथा अणु
		DEBUG_VAR(2, "(%s%d) ips_issue: logical cmd id %d",
			  ips_name, ha->host_num, scb->cmd.basic_io.command_id);
	पूर्ण

	ग_लिखोl(scb->scb_busaddr, ha->mem_ptr + IPS_REG_I2O_INMSGQ);

	वापस (IPS_SUCCESS);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_isपूर्णांकr_copperhead                                      */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Test to see अगर an पूर्णांकerrupt is क्रम us                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_isपूर्णांकr_copperhead(ips_ha_t * ha)
अणु
	uपूर्णांक8_t Isr;

	METHOD_TRACE("ips_isintr_copperhead", 2);

	Isr = inb(ha->io_addr + IPS_REG_HISR);

	अगर (Isr == 0xFF)
		/* ?!?! Nothing really there */
		वापस (0);

	अगर (Isr & IPS_BIT_SCE)
		वापस (1);
	अन्यथा अगर (Isr & (IPS_BIT_SQO | IPS_BIT_GHI)) अणु
		/* status queue overflow or GHI */
		/* just clear the पूर्णांकerrupt */
		outb(Isr, ha->io_addr + IPS_REG_HISR);
	पूर्ण

	वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_isपूर्णांकr_copperhead_memio                                */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Test to see अगर an पूर्णांकerrupt is क्रम us                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_isपूर्णांकr_copperhead_memio(ips_ha_t * ha)
अणु
	uपूर्णांक8_t Isr;

	METHOD_TRACE("ips_isintr_memio", 2);

	Isr = पढ़ोb(ha->mem_ptr + IPS_REG_HISR);

	अगर (Isr == 0xFF)
		/* ?!?! Nothing really there */
		वापस (0);

	अगर (Isr & IPS_BIT_SCE)
		वापस (1);
	अन्यथा अगर (Isr & (IPS_BIT_SQO | IPS_BIT_GHI)) अणु
		/* status queue overflow or GHI */
		/* just clear the पूर्णांकerrupt */
		ग_लिखोb(Isr, ha->mem_ptr + IPS_REG_HISR);
	पूर्ण

	वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_isपूर्णांकr_morpheus                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Test to see अगर an पूर्णांकerrupt is क्रम us                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_isपूर्णांकr_morpheus(ips_ha_t * ha)
अणु
	uपूर्णांक32_t Isr;

	METHOD_TRACE("ips_isintr_morpheus", 2);

	Isr = पढ़ोl(ha->mem_ptr + IPS_REG_I2O_HIR);

	अगर (Isr & IPS_BIT_I2O_OPQI)
		वापस (1);
	अन्यथा
		वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_रुको                                                   */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Wait क्रम a command to complete                                         */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_रुको(ips_ha_t * ha, पूर्णांक समय, पूर्णांक पूर्णांकr)
अणु
	पूर्णांक ret;
	पूर्णांक करोne;

	METHOD_TRACE("ips_wait", 1);

	ret = IPS_FAILURE;
	करोne = FALSE;

	समय *= IPS_ONE_SEC;	/* convert seconds */

	जबतक ((समय > 0) && (!करोne)) अणु
		अगर (पूर्णांकr == IPS_INTR_ON) अणु
			अगर (ha->रुकोflag == FALSE) अणु
				ret = IPS_SUCCESS;
				करोne = TRUE;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (पूर्णांकr == IPS_INTR_IORL) अणु
			अगर (ha->रुकोflag == FALSE) अणु
				/*
				 * controller generated an पूर्णांकerrupt to
				 * acknowledge completion of the command
				 * and ips_पूर्णांकr() has serviced the पूर्णांकerrupt.
				 */
				ret = IPS_SUCCESS;
				करोne = TRUE;
				अवरोध;
			पूर्ण

			/*
			 * NOTE: we alपढ़ोy have the io_request_lock so
			 * even अगर we get an पूर्णांकerrupt it won't get serviced
			 * until after we finish.
			 */

			(*ha->func.पूर्णांकr) (ha);
		पूर्ण

		/* This looks like a very evil loop, but it only करोes this during start-up */
		udelay(1000);
		समय--;
	पूर्ण

	वापस (ret);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_ग_लिखो_driver_status                                    */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Write OS/Driver version to Page 5 of the nvram on the controller       */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_ग_लिखो_driver_status(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	METHOD_TRACE("ips_write_driver_status", 1);

	अगर (!ips_पढ़ोग_लिखो_page5(ha, FALSE, पूर्णांकr)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to read NVRAM page 5.\n");

		वापस (0);
	पूर्ण

	/* check to make sure the page has a valid */
	/* signature */
	अगर (le32_to_cpu(ha->nvram->signature) != IPS_NVRAM_P5_SIG) अणु
		DEBUG_VAR(1,
			  "(%s%d) NVRAM page 5 has an invalid signature: %X.",
			  ips_name, ha->host_num, ha->nvram->signature);
		ha->nvram->signature = IPS_NVRAM_P5_SIG;
	पूर्ण

	DEBUG_VAR(2,
		  "(%s%d) Ad Type: %d, Ad Slot: %d, BIOS: %c%c%c%c %c%c%c%c.",
		  ips_name, ha->host_num, le16_to_cpu(ha->nvram->adapter_type),
		  ha->nvram->adapter_slot, ha->nvram->bios_high[0],
		  ha->nvram->bios_high[1], ha->nvram->bios_high[2],
		  ha->nvram->bios_high[3], ha->nvram->bios_low[0],
		  ha->nvram->bios_low[1], ha->nvram->bios_low[2],
		  ha->nvram->bios_low[3]);

	ips_get_bios_version(ha, पूर्णांकr);

	/* change values (as needed) */
	ha->nvram->operating_प्रणाली = IPS_OS_LINUX;
	ha->nvram->adapter_type = ha->ad_type;
	स_नकल((अक्षर *) ha->nvram->driver_high, IPS_VERSION_HIGH, 4);
	स_नकल((अक्षर *) ha->nvram->driver_low, IPS_VERSION_LOW, 4);
	स_नकल((अक्षर *) ha->nvram->bios_high, ha->bios_version, 4);
	स_नकल((अक्षर *) ha->nvram->bios_low, ha->bios_version + 4, 4);

	ha->nvram->versioning = 0;	/* Indicate the Driver Does Not Support Versioning */

	/* now update the page */
	अगर (!ips_पढ़ोग_लिखो_page5(ha, TRUE, पूर्णांकr)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to write NVRAM page 5.\n");

		वापस (0);
	पूर्ण

	/* IF NVRAM Page 5 is OK, Use it क्रम Slot Number Info Because Linux Doesn't Do Slots */
	ha->slot_num = ha->nvram->adapter_slot;

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_पढ़ो_adapter_status                                    */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Do an Inquiry command to the adapter                                   */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_पढ़ो_adapter_status(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;
	पूर्णांक ret;

	METHOD_TRACE("ips_read_adapter_status", 1);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_cmd_समयout;
	scb->cdb[0] = IPS_CMD_ENQUIRY;

	scb->cmd.basic_io.op_code = IPS_CMD_ENQUIRY;
	scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.basic_io.sg_count = 0;
	scb->cmd.basic_io.lba = 0;
	scb->cmd.basic_io.sector_count = 0;
	scb->cmd.basic_io.log_drv = 0;
	scb->data_len = माप (*ha->enq);
	scb->cmd.basic_io.sg_addr = ha->enq_busaddr;

	/* send command */
	अगर (((ret =
	      ips_send_रुको(ha, scb, ips_cmd_समयout, पूर्णांकr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1))
		वापस (0);

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_पढ़ो_subप्रणाली_parameters                              */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Read subप्रणाली parameters from the adapter                             */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_पढ़ो_subप्रणाली_parameters(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;
	पूर्णांक ret;

	METHOD_TRACE("ips_read_subsystem_parameters", 1);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_cmd_समयout;
	scb->cdb[0] = IPS_CMD_GET_SUBSYS;

	scb->cmd.basic_io.op_code = IPS_CMD_GET_SUBSYS;
	scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.basic_io.sg_count = 0;
	scb->cmd.basic_io.lba = 0;
	scb->cmd.basic_io.sector_count = 0;
	scb->cmd.basic_io.log_drv = 0;
	scb->data_len = माप (*ha->subsys);
	scb->cmd.basic_io.sg_addr = ha->ioctl_busaddr;

	/* send command */
	अगर (((ret =
	      ips_send_रुको(ha, scb, ips_cmd_समयout, पूर्णांकr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1))
		वापस (0);

	स_नकल(ha->subsys, ha->ioctl_data, माप(*ha->subsys));
	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_पढ़ो_config                                            */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Read the configuration on the adapter                                  */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_पढ़ो_config(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;
	पूर्णांक i;
	पूर्णांक ret;

	METHOD_TRACE("ips_read_config", 1);

	/* set शेषs क्रम initiator IDs */
	क्रम (i = 0; i < 4; i++)
		ha->conf->init_id[i] = 7;

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_cmd_समयout;
	scb->cdb[0] = IPS_CMD_READ_CONF;

	scb->cmd.basic_io.op_code = IPS_CMD_READ_CONF;
	scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);
	scb->data_len = माप (*ha->conf);
	scb->cmd.basic_io.sg_addr = ha->ioctl_busaddr;

	/* send command */
	अगर (((ret =
	      ips_send_रुको(ha, scb, ips_cmd_समयout, पूर्णांकr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1)) अणु

		स_रखो(ha->conf, 0, माप (IPS_CONF));

		/* reset initiator IDs */
		क्रम (i = 0; i < 4; i++)
			ha->conf->init_id[i] = 7;

		/* Allow Completed with Errors, so JCRM can access the Adapter to fix the problems */
		अगर ((scb->basic_status & IPS_GSC_STATUS_MASK) ==
		    IPS_CMD_CMPLT_WERROR)
			वापस (1);

		वापस (0);
	पूर्ण

	स_नकल(ha->conf, ha->ioctl_data, माप(*ha->conf));
	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_पढ़ोग_लिखो_page5                                        */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Read nvram page 5 from the adapter                                     */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_पढ़ोग_लिखो_page5(ips_ha_t * ha, पूर्णांक ग_लिखो, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;
	पूर्णांक ret;

	METHOD_TRACE("ips_readwrite_page5", 1);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_cmd_समयout;
	scb->cdb[0] = IPS_CMD_RW_NVRAM_PAGE;

	scb->cmd.nvram.op_code = IPS_CMD_RW_NVRAM_PAGE;
	scb->cmd.nvram.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.nvram.page = 5;
	scb->cmd.nvram.ग_लिखो = ग_लिखो;
	scb->cmd.nvram.reserved = 0;
	scb->cmd.nvram.reserved2 = 0;
	scb->data_len = माप (*ha->nvram);
	scb->cmd.nvram.buffer_addr = ha->ioctl_busaddr;
	अगर (ग_लिखो)
		स_नकल(ha->ioctl_data, ha->nvram, माप(*ha->nvram));

	/* issue the command */
	अगर (((ret =
	      ips_send_रुको(ha, scb, ips_cmd_समयout, पूर्णांकr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1)) अणु

		स_रखो(ha->nvram, 0, माप (IPS_NVRAM_P5));

		वापस (0);
	पूर्ण
	अगर (!ग_लिखो)
		स_नकल(ha->nvram, ha->ioctl_data, माप(*ha->nvram));
	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_clear_adapter                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   Clear the stripe lock tables                                           */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_clear_adapter(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;
	पूर्णांक ret;

	METHOD_TRACE("ips_clear_adapter", 1);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_reset_समयout;
	scb->cdb[0] = IPS_CMD_CONFIG_SYNC;

	scb->cmd.config_sync.op_code = IPS_CMD_CONFIG_SYNC;
	scb->cmd.config_sync.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.config_sync.channel = 0;
	scb->cmd.config_sync.source_target = IPS_POCL;
	scb->cmd.config_sync.reserved = 0;
	scb->cmd.config_sync.reserved2 = 0;
	scb->cmd.config_sync.reserved3 = 0;

	/* issue command */
	अगर (((ret =
	      ips_send_रुको(ha, scb, ips_reset_समयout, पूर्णांकr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1))
		वापस (0);

	/* send unlock stripe command */
	ips_init_scb(ha, scb);

	scb->cdb[0] = IPS_CMD_ERROR_TABLE;
	scb->समयout = ips_reset_समयout;

	scb->cmd.unlock_stripe.op_code = IPS_CMD_ERROR_TABLE;
	scb->cmd.unlock_stripe.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.unlock_stripe.log_drv = 0;
	scb->cmd.unlock_stripe.control = IPS_CSL;
	scb->cmd.unlock_stripe.reserved = 0;
	scb->cmd.unlock_stripe.reserved2 = 0;
	scb->cmd.unlock_stripe.reserved3 = 0;

	/* issue command */
	अगर (((ret =
	      ips_send_रुको(ha, scb, ips_cmd_समयout, पूर्णांकr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1))
		वापस (0);

	वापस (1);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_ffdc_reset                                             */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   FFDC: ग_लिखो reset info                                                 */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_ffdc_reset(ips_ha_t * ha, पूर्णांक पूर्णांकr)
अणु
	ips_scb_t *scb;

	METHOD_TRACE("ips_ffdc_reset", 1);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_cmd_समयout;
	scb->cdb[0] = IPS_CMD_FFDC;
	scb->cmd.ffdc.op_code = IPS_CMD_FFDC;
	scb->cmd.ffdc.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.ffdc.reset_count = ha->reset_count;
	scb->cmd.ffdc.reset_type = 0x80;

	/* convert समय to what the card wants */
	ips_fix_ffdc_समय(ha, scb, ha->last_ffdc);

	/* issue command */
	ips_send_रुको(ha, scb, ips_cmd_समयout, पूर्णांकr);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_ffdc_समय                                              */
/*                                                                          */
/* Routine Description:                                                     */
/*                                                                          */
/*   FFDC: ग_लिखो समय info                                                  */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_ffdc_समय(ips_ha_t * ha)
अणु
	ips_scb_t *scb;

	METHOD_TRACE("ips_ffdc_time", 1);

	DEBUG_VAR(1, "(%s%d) Sending time update.", ips_name, ha->host_num);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->समयout = ips_cmd_समयout;
	scb->cdb[0] = IPS_CMD_FFDC;
	scb->cmd.ffdc.op_code = IPS_CMD_FFDC;
	scb->cmd.ffdc.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.ffdc.reset_count = 0;
	scb->cmd.ffdc.reset_type = 0;

	/* convert समय to what the card wants */
	ips_fix_ffdc_समय(ha, scb, ha->last_ffdc);

	/* issue command */
	ips_send_रुको(ha, scb, ips_cmd_समयout, IPS_FFDC);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_fix_ffdc_समय                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*   Adjust समय_प्रकार to what the card wants                                   */
/*                                                                          */
/****************************************************************************/
अटल व्योम
ips_fix_ffdc_समय(ips_ha_t * ha, ips_scb_t * scb, समय64_t current_समय)
अणु
	काष्ठा पंचांग पंचांग;

	METHOD_TRACE("ips_fix_ffdc_time", 1);

	समय64_to_पंचांग(current_समय, 0, &पंचांग);

	scb->cmd.ffdc.hour   = पंचांग.पंचांग_hour;
	scb->cmd.ffdc.minute = पंचांग.पंचांग_min;
	scb->cmd.ffdc.second = पंचांग.पंचांग_sec;
	scb->cmd.ffdc.yearH  = (पंचांग.पंचांग_year + 1900) / 100;
	scb->cmd.ffdc.yearL  = पंचांग.पंचांग_year % 100;
	scb->cmd.ffdc.month  = पंचांग.पंचांग_mon + 1;
	scb->cmd.ffdc.day    = पंचांग.पंचांग_mday;
पूर्ण

/****************************************************************************
 * BIOS Flash Routines                                                      *
 ****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_erase_bios                                             */
/*                                                                          */
/* Routine Description:                                                     */
/*   Erase the BIOS on the adapter                                          */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_erase_bios(ips_ha_t * ha)
अणु
	पूर्णांक समयout;
	uपूर्णांक8_t status = 0;

	METHOD_TRACE("ips_erase_bios", 1);

	status = 0;

	/* Clear the status रेजिस्टर */
	outl(0, ha->io_addr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	outb(0x50, ha->io_addr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Setup */
	outb(0x20, ha->io_addr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Confirm */
	outb(0xD0, ha->io_addr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Status */
	outb(0x70, ha->io_addr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	समयout = 80000;	/* 80 seconds */

	जबतक (समयout > 0) अणु
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64) अणु
			outl(0, ha->io_addr + IPS_REG_FLAP);
			udelay(25);	/* 25 us */
		पूर्ण

		status = inb(ha->io_addr + IPS_REG_FLDP);

		अगर (status & 0x80)
			अवरोध;

		MDELAY(1);
		समयout--;
	पूर्ण

	/* check क्रम समयout */
	अगर (समयout <= 0) अणु
		/* समयout */

		/* try to suspend the erase */
		outb(0xB0, ha->io_addr + IPS_REG_FLDP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		/* रुको क्रम 10 seconds */
		समयout = 10000;
		जबतक (समयout > 0) अणु
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64) अणु
				outl(0, ha->io_addr + IPS_REG_FLAP);
				udelay(25);	/* 25 us */
			पूर्ण

			status = inb(ha->io_addr + IPS_REG_FLDP);

			अगर (status & 0xC0)
				अवरोध;

			MDELAY(1);
			समयout--;
		पूर्ण

		वापस (1);
	पूर्ण

	/* check क्रम valid VPP */
	अगर (status & 0x08)
		/* VPP failure */
		वापस (1);

	/* check क्रम successful flash */
	अगर (status & 0x30)
		/* sequence error */
		वापस (1);

	/* Otherwise, we were successful */
	/* clear status */
	outb(0x50, ha->io_addr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* enable पढ़ोs */
	outb(0xFF, ha->io_addr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_erase_bios_memio                                       */
/*                                                                          */
/* Routine Description:                                                     */
/*   Erase the BIOS on the adapter                                          */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_erase_bios_memio(ips_ha_t * ha)
अणु
	पूर्णांक समयout;
	uपूर्णांक8_t status;

	METHOD_TRACE("ips_erase_bios_memio", 1);

	status = 0;

	/* Clear the status रेजिस्टर */
	ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	ग_लिखोb(0x50, ha->mem_ptr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Setup */
	ग_लिखोb(0x20, ha->mem_ptr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Confirm */
	ग_लिखोb(0xD0, ha->mem_ptr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Status */
	ग_लिखोb(0x70, ha->mem_ptr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	समयout = 80000;	/* 80 seconds */

	जबतक (समयout > 0) अणु
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64) अणु
			ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
			udelay(25);	/* 25 us */
		पूर्ण

		status = पढ़ोb(ha->mem_ptr + IPS_REG_FLDP);

		अगर (status & 0x80)
			अवरोध;

		MDELAY(1);
		समयout--;
	पूर्ण

	/* check क्रम समयout */
	अगर (समयout <= 0) अणु
		/* समयout */

		/* try to suspend the erase */
		ग_लिखोb(0xB0, ha->mem_ptr + IPS_REG_FLDP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		/* रुको क्रम 10 seconds */
		समयout = 10000;
		जबतक (समयout > 0) अणु
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64) अणु
				ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
				udelay(25);	/* 25 us */
			पूर्ण

			status = पढ़ोb(ha->mem_ptr + IPS_REG_FLDP);

			अगर (status & 0xC0)
				अवरोध;

			MDELAY(1);
			समयout--;
		पूर्ण

		वापस (1);
	पूर्ण

	/* check क्रम valid VPP */
	अगर (status & 0x08)
		/* VPP failure */
		वापस (1);

	/* check क्रम successful flash */
	अगर (status & 0x30)
		/* sequence error */
		वापस (1);

	/* Otherwise, we were successful */
	/* clear status */
	ग_लिखोb(0x50, ha->mem_ptr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* enable पढ़ोs */
	ग_लिखोb(0xFF, ha->mem_ptr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_program_bios                                           */
/*                                                                          */
/* Routine Description:                                                     */
/*   Program the BIOS on the adapter                                        */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_program_bios(ips_ha_t * ha, अक्षर *buffer, uपूर्णांक32_t buffersize,
		 uपूर्णांक32_t offset)
अणु
	पूर्णांक i;
	पूर्णांक समयout;
	uपूर्णांक8_t status = 0;

	METHOD_TRACE("ips_program_bios", 1);

	status = 0;

	क्रम (i = 0; i < buffersize; i++) अणु
		/* ग_लिखो a byte */
		outl(i + offset, ha->io_addr + IPS_REG_FLAP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		outb(0x40, ha->io_addr + IPS_REG_FLDP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		outb(buffer[i], ha->io_addr + IPS_REG_FLDP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		/* रुको up to one second */
		समयout = 1000;
		जबतक (समयout > 0) अणु
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64) अणु
				outl(0, ha->io_addr + IPS_REG_FLAP);
				udelay(25);	/* 25 us */
			पूर्ण

			status = inb(ha->io_addr + IPS_REG_FLDP);

			अगर (status & 0x80)
				अवरोध;

			MDELAY(1);
			समयout--;
		पूर्ण

		अगर (समयout == 0) अणु
			/* समयout error */
			outl(0, ha->io_addr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			outb(0xFF, ha->io_addr + IPS_REG_FLDP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			वापस (1);
		पूर्ण

		/* check the status */
		अगर (status & 0x18) अणु
			/* programming error */
			outl(0, ha->io_addr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			outb(0xFF, ha->io_addr + IPS_REG_FLDP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			वापस (1);
		पूर्ण
	पूर्ण			/* end क्रम */

	/* Enable पढ़ोing */
	outl(0, ha->io_addr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	outb(0xFF, ha->io_addr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_program_bios_memio                                     */
/*                                                                          */
/* Routine Description:                                                     */
/*   Program the BIOS on the adapter                                        */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_program_bios_memio(ips_ha_t * ha, अक्षर *buffer, uपूर्णांक32_t buffersize,
		       uपूर्णांक32_t offset)
अणु
	पूर्णांक i;
	पूर्णांक समयout;
	uपूर्णांक8_t status = 0;

	METHOD_TRACE("ips_program_bios_memio", 1);

	status = 0;

	क्रम (i = 0; i < buffersize; i++) अणु
		/* ग_लिखो a byte */
		ग_लिखोl(i + offset, ha->mem_ptr + IPS_REG_FLAP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		ग_लिखोb(0x40, ha->mem_ptr + IPS_REG_FLDP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		ग_लिखोb(buffer[i], ha->mem_ptr + IPS_REG_FLDP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		/* रुको up to one second */
		समयout = 1000;
		जबतक (समयout > 0) अणु
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64) अणु
				ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
				udelay(25);	/* 25 us */
			पूर्ण

			status = पढ़ोb(ha->mem_ptr + IPS_REG_FLDP);

			अगर (status & 0x80)
				अवरोध;

			MDELAY(1);
			समयout--;
		पूर्ण

		अगर (समयout == 0) अणु
			/* समयout error */
			ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			ग_लिखोb(0xFF, ha->mem_ptr + IPS_REG_FLDP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			वापस (1);
		पूर्ण

		/* check the status */
		अगर (status & 0x18) अणु
			/* programming error */
			ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			ग_लिखोb(0xFF, ha->mem_ptr + IPS_REG_FLDP);
			अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			वापस (1);
		पूर्ण
	पूर्ण			/* end क्रम */

	/* Enable पढ़ोing */
	ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	ग_लिखोb(0xFF, ha->mem_ptr + IPS_REG_FLDP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_verअगरy_bios                                            */
/*                                                                          */
/* Routine Description:                                                     */
/*   Verअगरy the BIOS on the adapter                                         */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_verअगरy_bios(ips_ha_t * ha, अक्षर *buffer, uपूर्णांक32_t buffersize,
		uपूर्णांक32_t offset)
अणु
	uपूर्णांक8_t checksum;
	पूर्णांक i;

	METHOD_TRACE("ips_verify_bios", 1);

	/* test 1st byte */
	outl(0, ha->io_addr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	अगर (inb(ha->io_addr + IPS_REG_FLDP) != 0x55)
		वापस (1);

	outl(1, ha->io_addr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */
	अगर (inb(ha->io_addr + IPS_REG_FLDP) != 0xAA)
		वापस (1);

	checksum = 0xff;
	क्रम (i = 2; i < buffersize; i++) अणु

		outl(i + offset, ha->io_addr + IPS_REG_FLAP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		checksum = (uपूर्णांक8_t) checksum + inb(ha->io_addr + IPS_REG_FLDP);
	पूर्ण

	अगर (checksum != 0)
		/* failure */
		वापस (1);
	अन्यथा
		/* success */
		वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_verअगरy_bios_memio                                      */
/*                                                                          */
/* Routine Description:                                                     */
/*   Verअगरy the BIOS on the adapter                                         */
/*                                                                          */
/****************************************************************************/
अटल पूर्णांक
ips_verअगरy_bios_memio(ips_ha_t * ha, अक्षर *buffer, uपूर्णांक32_t buffersize,
		      uपूर्णांक32_t offset)
अणु
	uपूर्णांक8_t checksum;
	पूर्णांक i;

	METHOD_TRACE("ips_verify_bios_memio", 1);

	/* test 1st byte */
	ग_लिखोl(0, ha->mem_ptr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	अगर (पढ़ोb(ha->mem_ptr + IPS_REG_FLDP) != 0x55)
		वापस (1);

	ग_लिखोl(1, ha->mem_ptr + IPS_REG_FLAP);
	अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */
	अगर (पढ़ोb(ha->mem_ptr + IPS_REG_FLDP) != 0xAA)
		वापस (1);

	checksum = 0xff;
	क्रम (i = 2; i < buffersize; i++) अणु

		ग_लिखोl(i + offset, ha->mem_ptr + IPS_REG_FLAP);
		अगर (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		checksum =
		    (uपूर्णांक8_t) checksum + पढ़ोb(ha->mem_ptr + IPS_REG_FLDP);
	पूर्ण

	अगर (checksum != 0)
		/* failure */
		वापस (1);
	अन्यथा
		/* success */
		वापस (0);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_पात_init                                             */
/*                                                                          */
/* Routine Description:                                                     */
/*   cleanup routine क्रम a failed adapter initialization                    */
/****************************************************************************/
अटल पूर्णांक
ips_पात_init(ips_ha_t * ha, पूर्णांक index)
अणु
	ha->active = 0;
	ips_मुक्त(ha);
	ips_ha[index] = शून्य;
	ips_sh[index] = शून्य;
	वापस -1;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_shअगरt_controllers                                      */
/*                                                                          */
/* Routine Description:                                                     */
/*   helper function क्रम ordering adapters                                  */
/****************************************************************************/
अटल व्योम
ips_shअगरt_controllers(पूर्णांक lowindex, पूर्णांक highindex)
अणु
	ips_ha_t *ha_sav = ips_ha[highindex];
	काष्ठा Scsi_Host *sh_sav = ips_sh[highindex];
	पूर्णांक i;

	क्रम (i = highindex; i > lowindex; i--) अणु
		ips_ha[i] = ips_ha[i - 1];
		ips_sh[i] = ips_sh[i - 1];
		ips_ha[i]->host_num = i;
	पूर्ण
	ha_sav->host_num = lowindex;
	ips_ha[lowindex] = ha_sav;
	ips_sh[lowindex] = sh_sav;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_order_controllers                                      */
/*                                                                          */
/* Routine Description:                                                     */
/*   place controllers is the "proper" boot order                           */
/****************************************************************************/
अटल व्योम
ips_order_controllers(व्योम)
अणु
	पूर्णांक i, j, पंचांगp, position = 0;
	IPS_NVRAM_P5 *nvram;
	अगर (!ips_ha[0])
		वापस;
	nvram = ips_ha[0]->nvram;

	अगर (nvram->adapter_order[0]) अणु
		क्रम (i = 1; i <= nvram->adapter_order[0]; i++) अणु
			क्रम (j = position; j < ips_num_controllers; j++) अणु
				चयन (ips_ha[j]->ad_type) अणु
				हाल IPS_ADTYPE_SERVERAID6M:
				हाल IPS_ADTYPE_SERVERAID7M:
					अगर (nvram->adapter_order[i] == 'M') अणु
						ips_shअगरt_controllers(position,
								      j);
						position++;
					पूर्ण
					अवरोध;
				हाल IPS_ADTYPE_SERVERAID4L:
				हाल IPS_ADTYPE_SERVERAID4M:
				हाल IPS_ADTYPE_SERVERAID4MX:
				हाल IPS_ADTYPE_SERVERAID4LX:
					अगर (nvram->adapter_order[i] == 'N') अणु
						ips_shअगरt_controllers(position,
								      j);
						position++;
					पूर्ण
					अवरोध;
				हाल IPS_ADTYPE_SERVERAID6I:
				हाल IPS_ADTYPE_SERVERAID5I2:
				हाल IPS_ADTYPE_SERVERAID5I1:
				हाल IPS_ADTYPE_SERVERAID7k:
					अगर (nvram->adapter_order[i] == 'S') अणु
						ips_shअगरt_controllers(position,
								      j);
						position++;
					पूर्ण
					अवरोध;
				हाल IPS_ADTYPE_SERVERAID:
				हाल IPS_ADTYPE_SERVERAID2:
				हाल IPS_ADTYPE_NAVAJO:
				हाल IPS_ADTYPE_KIOWA:
				हाल IPS_ADTYPE_SERVERAID3L:
				हाल IPS_ADTYPE_SERVERAID3:
				हाल IPS_ADTYPE_SERVERAID4H:
					अगर (nvram->adapter_order[i] == 'A') अणु
						ips_shअगरt_controllers(position,
								      j);
						position++;
					पूर्ण
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		/* अगर adapter_order[0], then ordering is complete */
		वापस;
	पूर्ण
	/* old bios, use older ordering */
	पंचांगp = 0;
	क्रम (i = position; i < ips_num_controllers; i++) अणु
		अगर (ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID5I2 ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID5I1) अणु
			ips_shअगरt_controllers(position, i);
			position++;
			पंचांगp = 1;
		पूर्ण
	पूर्ण
	/* अगर there were no 5I cards, then करोn't करो any extra ordering */
	अगर (!पंचांगp)
		वापस;
	क्रम (i = position; i < ips_num_controllers; i++) अणु
		अगर (ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4L ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4M ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4LX ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4MX) अणु
			ips_shअगरt_controllers(position, i);
			position++;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_रेजिस्टर_scsi                                          */
/*                                                                          */
/* Routine Description:                                                     */
/*   perक्रमm any registration and setup with the scsi layer                 */
/****************************************************************************/
अटल पूर्णांक
ips_रेजिस्टर_scsi(पूर्णांक index)
अणु
	काष्ठा Scsi_Host *sh;
	ips_ha_t *ha, *oldha = ips_ha[index];
	sh = scsi_host_alloc(&ips_driver_ढाँचा, माप (ips_ha_t));
	अगर (!sh) अणु
		IPS_PRINTK(KERN_WARNING, oldha->pcidev,
			   "Unable to register controller with SCSI subsystem\n");
		वापस -1;
	पूर्ण
	ha = IPS_HA(sh);
	स_नकल(ha, oldha, माप (ips_ha_t));
	मुक्त_irq(oldha->pcidev->irq, oldha);
	/* Install the पूर्णांकerrupt handler with the new ha */
	अगर (request_irq(ha->pcidev->irq, करो_ipsपूर्णांकr, IRQF_SHARED, ips_name, ha)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to install interrupt handler\n");
		जाओ err_out_sh;
	पूर्ण

	kमुक्त(oldha);

	/* Store away needed values क्रम later use */
	sh->unique_id = (ha->io_addr) ? ha->io_addr : ha->mem_addr;
	sh->sg_tablesize = sh->hostt->sg_tablesize;
	sh->can_queue = sh->hostt->can_queue;
	sh->cmd_per_lun = sh->hostt->cmd_per_lun;
	sh->max_sectors = 128;

	sh->max_id = ha->ntarमाला_लो;
	sh->max_lun = ha->nlun;
	sh->max_channel = ha->nbus - 1;
	sh->can_queue = ha->max_cmds - 1;

	अगर (scsi_add_host(sh, &ha->pcidev->dev))
		जाओ err_out;

	ips_sh[index] = sh;
	ips_ha[index] = ha;

	scsi_scan_host(sh);

	वापस 0;

err_out:
	मुक्त_irq(ha->pcidev->irq, ha);
err_out_sh:
	scsi_host_put(sh);
	वापस -1;
पूर्ण

/*---------------------------------------------------------------------------*/
/*   Routine Name: ips_हटाओ_device                                         */
/*                                                                           */
/*   Routine Description:                                                    */
/*     Remove one Adapter ( Hot Plugging )                                   */
/*---------------------------------------------------------------------------*/
अटल व्योम
ips_हटाओ_device(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा Scsi_Host *sh = pci_get_drvdata(pci_dev);

	pci_set_drvdata(pci_dev, शून्य);

	ips_release(sh);

	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_module_init                                            */
/*                                                                          */
/* Routine Description:                                                     */
/*   function called on module load                                         */
/****************************************************************************/
अटल पूर्णांक __init
ips_module_init(व्योम)
अणु
#अगर !defined(__i386__) && !defined(__ia64__) && !defined(__x86_64__)
	prपूर्णांकk(KERN_ERR "ips: This driver has only been tested on the x86/ia64/x86_64 platforms\n");
	add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_STILL_OK);
#पूर्ण_अगर

	अगर (pci_रेजिस्टर_driver(&ips_pci_driver) < 0)
		वापस -ENODEV;
	ips_driver_ढाँचा.module = THIS_MODULE;
	ips_order_controllers();
	अगर (!ips_detect(&ips_driver_ढाँचा)) अणु
		pci_unरेजिस्टर_driver(&ips_pci_driver);
		वापस -ENODEV;
	पूर्ण
	रेजिस्टर_reboot_notअगरier(&ips_notअगरier);
	वापस 0;
पूर्ण

/****************************************************************************/
/*                                                                          */
/* Routine Name: ips_module_निकास                                            */
/*                                                                          */
/* Routine Description:                                                     */
/*   function called on module unload                                       */
/****************************************************************************/
अटल व्योम __निकास
ips_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ips_pci_driver);
	unरेजिस्टर_reboot_notअगरier(&ips_notअगरier);
पूर्ण

module_init(ips_module_init);
module_निकास(ips_module_निकास);

/*---------------------------------------------------------------------------*/
/*   Routine Name: ips_insert_device                                         */
/*                                                                           */
/*   Routine Description:                                                    */
/*     Add One Adapter ( Hot Plug )                                          */
/*                                                                           */
/*   Return Value:                                                           */
/*     0 अगर Successful, अन्यथा non-zero                                        */
/*---------------------------------------------------------------------------*/
अटल पूर्णांक
ips_insert_device(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक index = -1;
	पूर्णांक rc;

	METHOD_TRACE("ips_insert_device", 1);
	rc = pci_enable_device(pci_dev);
	अगर (rc)
		वापस rc;

	rc = pci_request_regions(pci_dev, "ips");
	अगर (rc)
		जाओ err_out;

	rc = ips_init_phase1(pci_dev, &index);
	अगर (rc == SUCCESS)
		rc = ips_init_phase2(index);

	अगर (ips_hotplug)
		अगर (ips_रेजिस्टर_scsi(index)) अणु
			ips_मुक्त(ips_ha[index]);
			rc = -1;
		पूर्ण

	अगर (rc == SUCCESS)
		ips_num_controllers++;

	ips_next_controller = ips_num_controllers;

	अगर (rc < 0) अणु
		rc = -ENODEV;
		जाओ err_out_regions;
	पूर्ण

	pci_set_drvdata(pci_dev, ips_sh[index]);
	वापस 0;

err_out_regions:
	pci_release_regions(pci_dev);
err_out:
	pci_disable_device(pci_dev);
	वापस rc;
पूर्ण

/*---------------------------------------------------------------------------*/
/*   Routine Name: ips_init_phase1                                           */
/*                                                                           */
/*   Routine Description:                                                    */
/*     Adapter Initialization                                                */
/*                                                                           */
/*   Return Value:                                                           */
/*     0 अगर Successful, अन्यथा non-zero                                        */
/*---------------------------------------------------------------------------*/
अटल पूर्णांक
ips_init_phase1(काष्ठा pci_dev *pci_dev, पूर्णांक *indexPtr)
अणु
	ips_ha_t *ha;
	uपूर्णांक32_t io_addr;
	uपूर्णांक32_t mem_addr;
	uपूर्णांक32_t io_len;
	uपूर्णांक32_t mem_len;
	पूर्णांक j;
	पूर्णांक index;
	dma_addr_t dma_address;
	अक्षर __iomem *ioremap_ptr;
	अक्षर __iomem *mem_ptr;
	uपूर्णांक32_t IsDead;

	METHOD_TRACE("ips_init_phase1", 1);
	index = IPS_MAX_ADAPTERS;
	क्रम (j = 0; j < IPS_MAX_ADAPTERS; j++) अणु
		अगर (ips_ha[j] == शून्य) अणु
			index = j;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (index >= IPS_MAX_ADAPTERS)
		वापस -1;

	/* Init MEM/IO addresses to 0 */
	mem_addr = 0;
	io_addr = 0;
	mem_len = 0;
	io_len = 0;

	क्रम (j = 0; j < 2; j++) अणु
		अगर (!pci_resource_start(pci_dev, j))
			अवरोध;

		अगर (pci_resource_flags(pci_dev, j) & IORESOURCE_IO) अणु
			io_addr = pci_resource_start(pci_dev, j);
			io_len = pci_resource_len(pci_dev, j);
		पूर्ण अन्यथा अणु
			mem_addr = pci_resource_start(pci_dev, j);
			mem_len = pci_resource_len(pci_dev, j);
		पूर्ण
	पूर्ण

	/* setup memory mapped area (अगर applicable) */
	अगर (mem_addr) अणु
		uपूर्णांक32_t base;
		uपूर्णांक32_t offs;

		base = mem_addr & PAGE_MASK;
		offs = mem_addr - base;
		ioremap_ptr = ioremap(base, PAGE_SIZE);
		अगर (!ioremap_ptr)
			वापस -1;
		mem_ptr = ioremap_ptr + offs;
	पूर्ण अन्यथा अणु
		ioremap_ptr = शून्य;
		mem_ptr = शून्य;
	पूर्ण

	/* found a controller */
	ha = kzalloc(माप (ips_ha_t), GFP_KERNEL);
	अगर (ha == शून्य) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate temporary ha struct\n");
		वापस -1;
	पूर्ण

	ips_sh[index] = शून्य;
	ips_ha[index] = ha;
	ha->active = 1;

	/* Store info in HA काष्ठाure */
	ha->io_addr = io_addr;
	ha->io_len = io_len;
	ha->mem_addr = mem_addr;
	ha->mem_len = mem_len;
	ha->mem_ptr = mem_ptr;
	ha->ioremap_ptr = ioremap_ptr;
	ha->host_num = (uपूर्णांक32_t) index;
	ha->slot_num = PCI_SLOT(pci_dev->devfn);
	ha->pcidev = pci_dev;

	/*
	 * Set the pci_dev's dma_mask.  Not all adapters support 64bit
	 * addressing so करोn't enable it if the adapter can't support
	 * it!  Also, करोn't use 64bit addressing अगर dma addresses
	 * are guaranteed to be < 4G.
	 */
	अगर (माप(dma_addr_t) > 4 && IPS_HAS_ENH_SGLIST(ha) &&
	    !dma_set_mask(&ha->pcidev->dev, DMA_BIT_MASK(64))) अणु
		(ha)->flags |= IPS_HA_ENH_SG;
	पूर्ण अन्यथा अणु
		अगर (dma_set_mask(&ha->pcidev->dev, DMA_BIT_MASK(32)) != 0) अणु
			prपूर्णांकk(KERN_WARNING "Unable to set DMA Mask\n");
			वापस ips_पात_init(ha, index);
		पूर्ण
	पूर्ण
	अगर(ips_cd_boot && !ips_FlashData)अणु
		ips_FlashData = dma_alloc_coherent(&pci_dev->dev,
				PAGE_SIZE << 7, &ips_flashbusaddr, GFP_KERNEL);
	पूर्ण

	ha->enq = dma_alloc_coherent(&pci_dev->dev, माप (IPS_ENQ),
			&ha->enq_busaddr, GFP_KERNEL);
	अगर (!ha->enq) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate host inquiry structure\n");
		वापस ips_पात_init(ha, index);
	पूर्ण

	ha->adapt = dma_alloc_coherent(&pci_dev->dev,
			माप (IPS_ADAPTER) + माप (IPS_IO_CMD),
			&dma_address, GFP_KERNEL);
	अगर (!ha->adapt) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate host adapt & dummy structures\n");
		वापस ips_पात_init(ha, index);
	पूर्ण
	ha->adapt->hw_status_start = dma_address;
	ha->dummy = (व्योम *) (ha->adapt + 1);



	ha->logical_drive_info = dma_alloc_coherent(&pci_dev->dev,
			माप (IPS_LD_INFO), &dma_address, GFP_KERNEL);
	अगर (!ha->logical_drive_info) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate logical drive info structure\n");
		वापस ips_पात_init(ha, index);
	पूर्ण
	ha->logical_drive_info_dma_addr = dma_address;


	ha->conf = kदो_स्मृति(माप (IPS_CONF), GFP_KERNEL);

	अगर (!ha->conf) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate host conf structure\n");
		वापस ips_पात_init(ha, index);
	पूर्ण

	ha->nvram = kदो_स्मृति(माप (IPS_NVRAM_P5), GFP_KERNEL);

	अगर (!ha->nvram) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate host NVRAM structure\n");
		वापस ips_पात_init(ha, index);
	पूर्ण

	ha->subsys = kदो_स्मृति(माप (IPS_SUBSYS), GFP_KERNEL);

	अगर (!ha->subsys) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate host subsystem structure\n");
		वापस ips_पात_init(ha, index);
	पूर्ण

	/* the ioctl buffer is now used during adapter initialization, so its
	 * successful allocation is now required */
	अगर (ips_ioctlsize < PAGE_SIZE)
		ips_ioctlsize = PAGE_SIZE;

	ha->ioctl_data = dma_alloc_coherent(&pci_dev->dev, ips_ioctlsize,
			&ha->ioctl_busaddr, GFP_KERNEL);
	ha->ioctl_len = ips_ioctlsize;
	अगर (!ha->ioctl_data) अणु
		IPS_PRINTK(KERN_WARNING, pci_dev,
			   "Unable to allocate IOCTL data\n");
		वापस ips_पात_init(ha, index);
	पूर्ण

	/*
	 * Setup Functions
	 */
	ips_setup_funclist(ha);

	अगर ((IPS_IS_MORPHEUS(ha)) || (IPS_IS_MARCO(ha))) अणु
		/* If Morpheus appears dead, reset it */
		IsDead = पढ़ोl(ha->mem_ptr + IPS_REG_I960_MSG1);
		अगर (IsDead == 0xDEADBEEF) अणु
			ips_reset_morpheus(ha);
		पूर्ण
	पूर्ण

	/*
	 * Initialize the card अगर it isn't alपढ़ोy
	 */

	अगर (!(*ha->func.isinit) (ha)) अणु
		अगर (!(*ha->func.init) (ha)) अणु
			/*
			 * Initialization failed
			 */
			IPS_PRINTK(KERN_WARNING, pci_dev,
				   "Unable to initialize controller\n");
			वापस ips_पात_init(ha, index);
		पूर्ण
	पूर्ण

	*indexPtr = index;
	वापस SUCCESS;
पूर्ण

/*---------------------------------------------------------------------------*/
/*   Routine Name: ips_init_phase2                                           */
/*                                                                           */
/*   Routine Description:                                                    */
/*     Adapter Initialization Phase 2                                        */
/*                                                                           */
/*   Return Value:                                                           */
/*     0 अगर Successful, अन्यथा non-zero                                        */
/*---------------------------------------------------------------------------*/
अटल पूर्णांक
ips_init_phase2(पूर्णांक index)
अणु
	ips_ha_t *ha;

	ha = ips_ha[index];

	METHOD_TRACE("ips_init_phase2", 1);
	अगर (!ha->active) अणु
		ips_ha[index] = शून्य;
		वापस -1;
	पूर्ण

	/* Install the पूर्णांकerrupt handler */
	अगर (request_irq(ha->pcidev->irq, करो_ipsपूर्णांकr, IRQF_SHARED, ips_name, ha)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to install interrupt handler\n");
		वापस ips_पात_init(ha, index);
	पूर्ण

	/*
	 * Allocate a temporary SCB क्रम initialization
	 */
	ha->max_cmds = 1;
	अगर (!ips_allocatescbs(ha)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to allocate a CCB\n");
		मुक्त_irq(ha->pcidev->irq, ha);
		वापस ips_पात_init(ha, index);
	पूर्ण

	अगर (!ips_hainit(ha)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to initialize controller\n");
		मुक्त_irq(ha->pcidev->irq, ha);
		वापस ips_पात_init(ha, index);
	पूर्ण
	/* Free the temporary SCB */
	ips_deallocatescbs(ha, 1);

	/* allocate CCBs */
	अगर (!ips_allocatescbs(ha)) अणु
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to allocate CCBs\n");
		मुक्त_irq(ha->pcidev->irq, ha);
		वापस ips_पात_init(ha, index);
	पूर्ण

	वापस SUCCESS;
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IBM ServeRAID Adapter Driver " IPS_VER_STRING);
MODULE_VERSION(IPS_VER_STRING);
