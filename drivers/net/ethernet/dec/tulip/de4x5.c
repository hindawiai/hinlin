<शैली गुरु>
/*  de4x5.c: A DIGITAL DC21x4x DECchip and DE425/DE434/DE435/DE450/DE500
             ethernet driver क्रम Linux.

    Copyright 1994, 1995 Digital Equipment Corporation.

    Testing resources क्रम this driver have been made available
    in part by NASA Ames Research Center (mjacob@nas.nasa.gov).

    The author may be reached at davies@maniac.ultranet.com.

    This program is मुक्त software; you can redistribute  it and/or modअगरy it
    under  the terms of  the GNU General  Public License as published by the
    Free Software Foundation;  either version 2 of the  License, or (at your
    option) any later version.

    THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR   IMPLIED
    WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
    NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT,  INसूचीECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
    USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
    ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    You should have received a copy of the  GNU General Public License aदीर्घ
    with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
    675 Mass Ave, Cambridge, MA 02139, USA.

    Originally,   this  driver  was    written  क्रम the  Digital   Equipment
    Corporation series of EtherWORKS ethernet cards:

        DE425 TP/COAX EISA
	DE434 TP PCI
	DE435 TP/COAX/AUI PCI
	DE450 TP/COAX/AUI PCI
	DE500 10/100 PCI Fasternet

    but it  will  now attempt  to  support all  cards which   conक्रमm to the
    Digital Semiconductor   SROM   Specअगरication.    The  driver   currently
    recognises the following chips:

        DC21040  (no SROM)
	DC21041[A]
	DC21140[A]
	DC21142
	DC21143

    So far the driver is known to work with the following cards:

        KINGSTON
	Linksys
	ZNYX342
	SMC8432
	SMC9332 (w/new SROM)
	ZNYX31[45]
	ZNYX346 10/100 4 port (can act as a 10/100 bridge!)

    The driver has been tested on a relatively busy network using the DE425,
    DE434, DE435 and DE500 cards and benchmarked with 'ttcp': it transferred
    16M of data to a DECstation 5000/200 as follows:

                TCP           UDP
             TX     RX     TX     RX
    DE425   1030k  997k   1170k  1128k
    DE434   1063k  995k   1170k  1125k
    DE435   1063k  995k   1170k  1125k
    DE500   1063k  998k   1170k  1125k  in 10Mb/s mode

    All  values are typical (in   kBytes/sec) from a  sample  of 4 क्रम  each
    measurement. Their error is +/-20k on a quiet (निजी) network and also
    depend on what load the CPU has.

    =========================================================================
    This driver  has been written substantially  from  scratch, although its
    inheritance of style and stack पूर्णांकerface from 'ewrk3.c' and in turn from
    Donald Becker's 'lance.c' should be obvious. With the module स्वतःload of
    every  usable DECchip board,  I  pinched Donald's 'next_module' field to
    link my modules together.

    Up to 15 EISA cards can be supported under this driver, limited primarily
    by the available IRQ lines.  I have  checked dअगरferent configurations of
    multiple depca, EtherWORKS 3 cards and de4x5 cards and  have not found a
    problem yet (provided you have at least depca.c v0.38) ...

    PCI support has been added  to allow the driver  to work with the DE434,
    DE435, DE450 and DE500 cards. The I/O accesses are a bit of a kludge due
    to the dअगरferences in the EISA and PCI CSR address offsets from the base
    address.

    The ability to load this  driver as a loadable  module has been included
    and used extensively  during the driver development  (to save those दीर्घ
    reboot sequences).  Loadable module support  under PCI and EISA has been
    achieved by letting the driver स्वतःprobe as अगर it were compiled पूर्णांकo the
    kernel. Do make sure  you're not sharing  पूर्णांकerrupts with anything  that
    cannot accommodate  पूर्णांकerrupt  sharing!

    To utilise this ability, you have to करो 8 things:

    0) have a copy of the loadable modules code installed on your प्रणाली.
    1) copy de4x5.c from the  /linux/drivers/net directory to your favourite
    temporary directory.
    2) क्रम fixed  स्वतःprobes (not  recommended),  edit the source code  near
    line 5594 to reflect the I/O address  you're using, or assign these when
    loading by:

                   insmod de4x5 io=0xghh           where g = bus number
		                                        hh = device number

       NB: स्वतःprobing क्रम modules is now supported by शेष. You may just
           use:

                   insmod de4x5

           to load all available boards. For a specअगरic board, still use
	   the 'io=?' above.
    3) compile  de4x5.c, but include -DMODULE in  the command line to ensure
    that the correct bits are compiled (see end of source code).
    4) अगर you are wanting to add a new  card, जाओ 5. Otherwise, recompile a
    kernel with the de4x5 configuration turned off and reboot.
    5) insmod de4x5 [io=0xghh]
    6) run the net startup bits क्रम your new eth?? पूर्णांकerface(s) manually
    (usually /etc/rc.inet[12] at boot समय).
    7) enjoy!

    To unload a module, turn off the associated पूर्णांकerface(s)
    'ifconfig eth?? down' then 'rmmod de4x5'.

    Automedia detection is included so that in  principal you can disconnect
    from, e.g.  TP, reconnect  to BNC  and  things will still work  (after a
    छोड़ो whilst the   driver figures out   where its media went).  My tests
    using ping showed that it appears to work....

    By  शेष,  the driver will  now   स्वतःdetect any  DECchip based card.
    Should you have a need to restrict the driver to DIGITAL only cards, you
    can compile with a  DEC_ONLY define, or अगर  loading as a module, use the
    'dec_only=1'  parameter.

    I've changed the timing routines to  use the kernel समयr and scheduling
    functions  so that the  hangs  and other assorted problems that occurred
    जबतक स्वतःsensing the  media  should be gone.  A  bonus  क्रम the DC21040
    स्वतः  media sense algorithm is  that it can now  use one that is more in
    line with the  rest (the DC21040  chip करोesn't  have a hardware  समयr).
    The करोwnside is the 1 'jiffies' (10ms) resolution.

    IEEE 802.3u MII पूर्णांकerface code has  been added in anticipation that some
    products may use it in the future.

    The SMC9332 card  has a non-compliant SROM  which needs fixing -  I have
    patched this  driver to detect it  because the SROM क्रमmat used complies
    to a previous DEC-STD क्रमmat.

    I have हटाओd the buffer copies needed क्रम receive on Intels.  I cannot
    हटाओ them क्रम   Alphas since  the  Tulip hardware   only करोes दीर्घword
    aligned  DMA transfers  and  the  Alphas get   alignment traps with  non
    दीर्घword aligned data copies (which makes them really slow). No comment.

    I  have added SROM decoding  routines to make this  driver work with any
    card that  supports the Digital  Semiconductor SROM spec. This will help
    all  cards running the dc2114x  series chips in particular.  Cards using
    the dc2104x  chips should run correctly with  the basic  driver.  I'm in
    debt to <mjacob@feral.com> क्रम the  testing and feedback that helped get
    this feature working.  So far we have  tested KINGSTON, SMC8432, SMC9332
    (with the latest SROM complying  with the SROM spec  V3: their first was
    broken), ZNYX342  and  LinkSys. ZYNX314 (dual  21041  MAC) and  ZNYX 315
    (quad 21041 MAC)  cards also  appear  to work despite their  incorrectly
    wired IRQs.

    I have added a temporary fix क्रम पूर्णांकerrupt problems when some SCSI cards
    share the same पूर्णांकerrupt as the DECchip based  cards. The problem occurs
    because  the SCSI card wants to  grab the पूर्णांकerrupt  as a fast पूर्णांकerrupt
    (runs the   service routine with पूर्णांकerrupts turned   off) vs.  this card
    which really needs to run the service routine with पूर्णांकerrupts turned on.
    This driver will  now   add the पूर्णांकerrupt service   routine  as  a  fast
    पूर्णांकerrupt अगर it   is bounced from the   slow पूर्णांकerrupt.  THIS IS NOT   A
    RECOMMENDED WAY TO RUN THE DRIVER  and has been करोne  क्रम a limited समय
    until  people   sort  out their  compatibility    issues and the  kernel
    पूर्णांकerrupt  service code  is  fixed.   YOU  SHOULD SEPARATE OUT  THE FAST
    INTERRUPT CARDS FROM THE SLOW INTERRUPT CARDS to ensure that they करो not
    run on the same पूर्णांकerrupt. PCMCIA/CardBus is another can of worms...

    Finally, I think  I have really  fixed  the module  loading problem with
    more than one DECchip based  card.  As a  side effect, I करोn't mess with
    the  device काष्ठाure any  more which means that  अगर more than 1 card in
    2.0.x is    installed (4  in   2.1.x),  the  user   will have   to  edit
    linux/drivers/net/Space.c  to make room क्रम  them. Hence, module loading
    is  the preferred way to use   this driver, since  it  करोesn't have this
    limitation.

    Where SROM media  detection is used and  full duplex is specअगरied in the
    SROM,  the feature is  ignored unless  lp->params.fdx  is set at compile
    समय  OR during  a   module load  (insmod  de4x5   args='eth??:fdx' [see
    below]).  This is because there  is no way  to स्वतःmatically detect full
    duplex   links  except through   स्वतःnegotiation.    When I  include the
    स्वतःnegotiation feature in  the SROM स्वतःconf  code, this detection will
    occur स्वतःmatically क्रम that हाल.

    Command  line arguments are  now  allowed, similar  to passing arguments
    through LILO. This will allow a per adapter board  set up of full duplex
    and media. The only lexical स्थिरraपूर्णांकs  are: the board name (dev->name)
    appears in the list beक्रमe its  parameters.  The list of parameters ends
    either at the end of the parameter list or with another board name.  The
    following parameters are allowed:

            fdx        क्रम full duplex
	    स्वतःsense  to set the media/speed; with the following
	               sub-parameters:
		       TP, TP_NW, BNC, AUI, BNC_AUI, 100Mb, 10Mb, AUTO

    Case sensitivity is important  क्रम  the sub-parameters. They *must*   be
    upper हाल. Examples:

        insmod de4x5 args='eth1:fdx autosense=BNC eth0:autosense=100Mb'.

    For a compiled in driver, at or above line 548, place e.g.
	#घोषणा DE4X5_PARM "eth0:fdx autosense=AUI eth2:autosense=TP"

    Yes,  I know full duplex isn't  permissible on BNC  or AUI; they're just
    examples. By शेष, full duplex is turned off and  AUTO is the शेष
    स्वतःsense setting.  In reality, I expect only  the full duplex option to
    be used. Note the use of single quotes in the two examples above and the
    lack of commas to separate items. ALSO, you must get the requested media
    correct in relation to what the adapter SROM says it has. There's no way
    to  determine this in  advance other than by  trial and error and common
    sense, e.g. call a BNC connectored port 'BNC', not '10Mb'.

    Changed the bus probing.  EISA used to be  करोne first,  followed by PCI.
    Most people probably करोn't even know  what a de425 is today and the EISA
    probe has messed  up some SCSI cards  in the past,  so now PCI is always
    probed  first  followed by  EISA अगर  a) the architecture allows EISA and
    either  b) there have been no PCI cards detected or  c) an EISA probe is
    क्रमced by  the user.  To क्रमce  a probe  include  "force_eisa"  in  your
    insmod "args" line;  क्रम built-in kernels either change the driver to करो
    this  स्वतःmatically  or include  #घोषणा DE4X5_FORCE_EISA  on or  beक्रमe
    line 1040 in the driver.

    TO DO:
    ------

    Revision History
    ----------------

    Version   Date        Description

      0.1     17-Nov-94   Initial writing. ALPHA code release.
      0.2     13-Jan-95   Added PCI support क्रम DE435's.
      0.21    19-Jan-95   Added स्वतः media detection.
      0.22    10-Feb-95   Fix पूर्णांकerrupt handler call <chris@cosy.sbg.ac.at>.
                          Fix recognition bug reported by <bkm@star.rl.ac.uk>.
			  Add request/release_region code.
			  Add loadable modules support क्रम PCI.
			  Clean up loadable modules support.
      0.23    28-Feb-95   Added DC21041 and DC21140 support.
                          Fix missed frame counter value and initialisation.
			  Fixed EISA probe.
      0.24    11-Apr-95   Change delay routine to use <linux/udelay>.
                          Change TX_BUFFS_AVAIL macro.
			  Change media स्वतःdetection to allow manual setting.
			  Completed DE500 (DC21140) support.
      0.241   18-Apr-95   Interim release without DE500 Autosense Algorithm.
      0.242   10-May-95   Minor changes.
      0.30    12-Jun-95   Timer fix क्रम DC21140.
                          Portability changes.
			  Add ALPHA changes from <jestabro@ant.tay1.dec.com>.
			  Add DE500 semi स्वतःmatic स्वतःsense.
			  Add Link Fail पूर्णांकerrupt TP failure detection.
			  Add समयr based link change detection.
			  Plugged a memory leak in de4x5_queue_pkt().
      0.31    13-Jun-95   Fixed PCI stuff क्रम 1.3.1.
      0.32    26-Jun-95   Added verअगरy_area() calls in de4x5_ioctl() from a
                          suggestion by <heiko@colossus.escape.de>.
      0.33     8-Aug-95   Add shared पूर्णांकerrupt support (not released yet).
      0.331   21-Aug-95   Fix de4x5_खोलो() with fast CPUs.
                          Fix de4x5_पूर्णांकerrupt().
                          Fix dc21140_स्वतःconf() mess.
			  No shared पूर्णांकerrupt support.
      0.332   11-Sep-95   Added MII management पूर्णांकerface routines.
      0.40     5-Mar-96   Fix setup frame समयout <maartenb@hpkuipc.cern.ch>.
                          Add kernel समयr code (h/w is too flaky).
			  Add MII based PHY स्वतःsense.
			  Add new multicasting code.
			  Add new स्वतःsense algorithms क्रम media/mode
			  selection using kernel scheduling/timing.
			  Re-क्रमmatted.
			  Made changes suggested by <jeff@router.patch.net>:
			    Change driver to detect all DECchip based cards
			    with DEC_ONLY restriction a special हाल.
			    Changed driver to स्वतःprobe as a module. No irq
			    checking is करोne now - assume BIOS is good!
			  Added SMC9332 detection <manabe@Roy.dsl.tutics.ac.jp>
      0.41    21-Mar-96   Don't check क्रम get_hw_addr checksum unless DEC card
                          only <niles@axp745gsfc.nasa.gov>
			  Fix क्रम multiple PCI cards reported by <jos@xos.nl>
			  Duh, put the IRQF_SHARED flag पूर्णांकo request_पूर्णांकerrupt().
			  Fix SMC ethernet address in enet_det[].
			  Prपूर्णांक chip name instead of "UNKNOWN" during boot.
      0.42    26-Apr-96   Fix MII ग_लिखो TA bit error.
                          Fix bug in dc21040 and dc21041 स्वतःsense code.
			  Remove buffer copies on receive क्रम Intels.
			  Change sk_buff handling during media disconnects to
			   eliminate DUP packets.
			  Add dynamic TX thresholding.
			  Change all chips to use perfect multicast filtering.
			  Fix alloc_device() bug <jari@markkus2.fimr.fi>
      0.43   21-Jun-96    Fix unconnected media TX retry bug.
                          Add Accton to the list of broken cards.
			  Fix TX under-run bug क्रम non DC21140 chips.
			  Fix boot command probe bug in alloc_device() as
			   reported by <koen.gadeyne@barco.com> and
			   <orava@nether.tky.hut.fi>.
			  Add cache locks to prevent a race condition as
			   reported by <csd@microplex.com> and
			   <baba@beckman.uiuc.edu>.
			  Upgraded alloc_device() code.
      0.431  28-Jun-96    Fix potential bug in queue_pkt() from discussion
                          with <csd@microplex.com>
      0.44   13-Aug-96    Fix RX overflow bug in 2114[023] chips.
                          Fix EISA probe bugs reported by <os2@kpi.kharkov.ua>
			  and <michael@compurex.com>.
      0.441   9-Sep-96    Change dc21041_स्वतःconf() to probe quiet BNC media
                           with a loopback packet.
      0.442   9-Sep-96    Include AUI in dc21041 media prपूर्णांकout. Bug reported
                           by <bhat@munकरोok.cs.mu.OZ.AU>
      0.45    8-Dec-96    Include endian functions क्रम PPC use, from work
                           by <cort@cs.nmt.edu> and <g.thomas@खोलोgroup.org>.
      0.451  28-Dec-96    Added fix to allow स्वतःprobe क्रम modules after
                           suggestion from <mjacob@feral.com>.
      0.5    30-Jan-97    Added SROM decoding functions.
                          Updated debug flags.
			  Fix sleep/wakeup calls क्रम PCI cards, bug reported
			   by <cross@gweep.lkg.dec.com>.
			  Added multi-MAC, one SROM feature from discussion
			   with <mjacob@feral.com>.
			  Added full module स्वतःprobe capability.
			  Added attempt to use an SMC9332 with broken SROM.
			  Added fix क्रम ZYNX multi-mac cards that didn't
			   get their IRQs wired correctly.
      0.51   13-Feb-97    Added endian fixes क्रम the SROM accesses from
			   <paubert@iram.es>
			  Fix init_connection() to हटाओ extra device reset.
			  Fix MAC/PHY reset ordering in dc21140m_स्वतःconf().
			  Fix initialisation problem with lp->समयout in
			   typeX_infoblock() from <paubert@iram.es>.
			  Fix MII PHY reset problem from work करोne by
			   <paubert@iram.es>.
      0.52   26-Apr-97    Some changes may not credit the right people -
                           a disk crash meant I lost some mail.
			  Change RX पूर्णांकerrupt routine to drop rather than
			   defer packets to aव्योम hang reported by
			   <g.thomas@खोलोgroup.org>.
			  Fix srom_exec() to वापस क्रम COMPACT and type 1
			   infoblocks.
			  Added DC21142 and DC21143 functions.
			  Added byte counters from <phil@tazenda.demon.co.uk>
			  Added IRQF_DISABLED temporary fix from
			   <mjacob@feral.com>.
      0.53   12-Nov-97    Fix the *_probe() to include 'eth??' name during
                           module load: bug reported by
			   <Piete.Brooks@cl.cam.ac.uk>
			  Fix multi-MAC, one SROM, to work with 2114x chips:
			   bug reported by <cmetz@inner.net>.
			  Make above search independent of BIOS device scan
			   direction.
			  Completed DC2114[23] स्वतःsense functions.
      0.531  21-Dec-97    Fix DE500-XA 100Mb/s bug reported by
                           <robin@पूर्णांकercore.com
			  Fix type1_infoblock() bug पूर्णांकroduced in 0.53, from
			   problem reports by
			   <parmee@postecss.ncrfran.france.ncr.com> and
			   <jo@ice.dillingen.baynet.de>.
			  Added argument list to set up each board from either
			   a module's command line or a compiled in #घोषणा.
			  Added generic MII PHY functionality to deal with
			   newer PHY chips.
			  Fix the mess in 2.1.67.
      0.532   5-Jan-98    Fix bug in mii_get_phy() reported by
                           <redhat@cococo.net>.
                          Fix bug in pci_probe() क्रम 64 bit प्रणालीs reported
			   by <belliott@accessone.com>.
      0.533   9-Jan-98    Fix more 64 bit bugs reported by <jal@cs.brown.edu>.
      0.534  24-Jan-98    Fix last (?) endian bug from <geert@linux-m68k.org>
      0.535  21-Feb-98    Fix Ethernet Address PROM reset bug क्रम DC21040.
      0.536  21-Mar-98    Change pci_probe() to use the pci_dev काष्ठाure.
			  **Incompatible with 2.0.x from here.**
      0.540   5-Jul-98    Atomicize निश्चितion of dev->पूर्णांकerrupt क्रम SMP
                           from <lma@varesearch.com>
			  Add TP, AUI and BNC हालs to 21140m_स्वतःconf() क्रम
			   हाल where a 21140 under SROM control uses, e.g. AUI
			   from problem report by <delchini@lpnp09.in2p3.fr>
			  Add MII parallel detection to 2114x_स्वतःconf() क्रम
			   हाल where no स्वतःnegotiation partner exists from
			   problem report by <mlapsley@ndirect.co.uk>.
			  Add ability to क्रमce connection type directly even
			   when using SROM control from problem report by
			   <earl@exis.net>.
			  Updated the PCI पूर्णांकerface to conक्रमm with the latest
			   version. I hope nothing is broken...
          		  Add TX करोne पूर्णांकerrupt modअगरication from suggestion
			   by <Austin.Donnelly@cl.cam.ac.uk>.
			  Fix is_anc_capable() bug reported by
			   <Austin.Donnelly@cl.cam.ac.uk>.
			  Fix type[13]_infoblock() bug: during MII search, PHY
			   lp->rst not run because lp->ibn not initialised -
			   from report & fix by <paubert@iram.es>.
			  Fix probe bug with EISA & PCI cards present from
                           report by <eirik@netcom.com>.
      0.541  24-Aug-98    Fix compiler problems associated with i386-string
                           ops from multiple bug reports and temporary fix
			   from <paubert@iram.es>.
			  Fix pci_probe() to correctly emulate the old
			   pcibios_find_class() function.
			  Add an_exception() क्रम old ZYNX346 and fix compile
			   warning on PPC & SPARC, from <ecd@skynet.be>.
			  Fix lastPCI to correctly work with compiled in
			   kernels and modules from bug report by
			   <Zlatko.Calusic@CARNet.hr> et al.
      0.542  15-Sep-98    Fix dc2114x_स्वतःconf() to stop multiple messages
                           when media is unconnected.
			  Change dev->पूर्णांकerrupt to lp->पूर्णांकerrupt to ensure
			   alignment क्रम Alpha's and aव्योम their unaligned
			   access traps. This flag is merely क्रम log messages:
			   should करो something more definitive though...
      0.543  30-Dec-98    Add SMP spin locking.
      0.544   8-May-99    Fix क्रम buggy SROM in Motorola embedded boards using
                           a 21143 by <mmporter@home.com>.
			  Change PCI/EISA bus probing order.
      0.545  28-Nov-99    Further Moto SROM bug fix from
                           <mporter@eng.mcd.mot.com>
                          Remove द्विगुन checking क्रम DEBUG_RX in de4x5_dbg_rx()
			   from report by <geert@linux-m68k.org>
      0.546  22-Feb-01    Fixes Alpha XP1000 oops.  The srom_search function
                           was causing a page fault when initializing the
                           variable 'pb', on a non de4x5 PCI device, in this
                           हाल a PCI bridge (DEC chip 21152). The value of
                           'pb' is now only initialized अगर a de4x5 chip is
                           present.
                           <france@handhelds.org>
      0.547  08-Nov-01    Use library crc32 functions by <Matt_Domsch@dell.com>
      0.548  30-Aug-03    Big 2.6 cleanup. Ported to PCI/EISA probing and
                           generic DMA APIs. Fixed DE425 support on Alpha.
			   <maz@wild-wind.fr.eu.org>
    =========================================================================
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/eisa.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>
#समावेश <linux/unistd.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/uaccess.h>
#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/machdep.h>
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

#समावेश "de4x5.h"

अटल स्थिर अक्षर version[] =
	KERN_INFO "de4x5.c:V0.546 2001/02/22 davies@maniac.ultranet.com\n";

#घोषणा c_अक्षर स्थिर अक्षर

/*
** MII Inक्रमmation
*/
काष्ठा phy_table अणु
    पूर्णांक reset;              /* Hard reset required?                         */
    पूर्णांक id;                 /* IEEE OUI                                     */
    पूर्णांक ta;                 /* One cycle TA समय - 802.3u is confusing here */
    काष्ठा अणु                /* Non स्वतःnegotiation (parallel) speed det.    */
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक value;
    पूर्ण spd;
पूर्ण;

काष्ठा mii_phy अणु
    पूर्णांक reset;              /* Hard reset required?                      */
    पूर्णांक id;                 /* IEEE OUI                                  */
    पूर्णांक ta;                 /* One cycle TA समय                         */
    काष्ठा अणु                /* Non स्वतःnegotiation (parallel) speed det. */
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक value;
    पूर्ण spd;
    पूर्णांक addr;               /* MII address क्रम the PHY                   */
    u_अक्षर  *gep;           /* Start of GEP sequence block in SROM       */
    u_अक्षर  *rst;           /* Start of reset sequence in SROM           */
    u_पूर्णांक mc;               /* Media Capabilities                        */
    u_पूर्णांक ana;              /* NWay Advertisement                        */
    u_पूर्णांक fdx;              /* Full DupleX capabilities क्रम each media   */
    u_पूर्णांक tपंचांग;              /* Transmit Threshold Mode क्रम each media    */
    u_पूर्णांक mci;              /* 21142 MII Connector Interrupt info        */
पूर्ण;

#घोषणा DE4X5_MAX_PHY 8     /* Allow up to 8 attached PHY devices per board */

काष्ठा sia_phy अणु
    u_अक्षर mc;              /* Media Code                                */
    u_अक्षर ext;             /* csr13-15 valid when set                   */
    पूर्णांक csr13;              /* SIA Connectivity Register                 */
    पूर्णांक csr14;              /* SIA TX/RX Register                        */
    पूर्णांक csr15;              /* SIA General Register                      */
    पूर्णांक gepc;               /* SIA GEP Control Inक्रमmation               */
    पूर्णांक gep;                /* SIA GEP Data                              */
पूर्ण;

/*
** Define the know universe of PHY devices that can be
** recognised by this driver.
*/
अटल काष्ठा phy_table phy_info[] = अणु
    अणु0, NATIONAL_TX, 1, अणु0x19, 0x40, 0x00पूर्णपूर्ण,       /* National TX      */
    अणु1, BROADCOM_T4, 1, अणु0x10, 0x02, 0x02पूर्णपूर्ण,       /* Broadcom T4      */
    अणु0, SEEQ_T4    , 1, अणु0x12, 0x10, 0x10पूर्णपूर्ण,       /* SEEQ T4          */
    अणु0, CYPRESS_T4 , 1, अणु0x05, 0x20, 0x20पूर्णपूर्ण,       /* Cypress T4       */
    अणु0, 0x7810     , 1, अणु0x14, 0x0800, 0x0800पूर्णपूर्ण    /* Level One LTX970 */
पूर्ण;

/*
** These GENERIC values assumes that the PHY devices follow 802.3u and
** allow parallel detection to set the link partner ability रेजिस्टर.
** Detection of 100Base-TX [H/F Duplex] and 100Base-T4 is supported.
*/
#घोषणा GENERIC_REG   0x05      /* Autoneg. Link Partner Advertisement Reg. */
#घोषणा GENERIC_MASK  MII_ANLPA_100M /* All 100Mb/s Technologies            */
#घोषणा GENERIC_VALUE MII_ANLPA_100M /* 100B-TX, 100B-TX FDX, 100B-T4       */

/*
** Define special SROM detection हालs
*/
अटल c_अक्षर enet_det[][ETH_ALEN] = अणु
    अणु0x00, 0x00, 0xc0, 0x00, 0x00, 0x00पूर्ण,
    अणु0x00, 0x00, 0xe8, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

#घोषणा SMC    1
#घोषणा ACCTON 2

/*
** SROM Repair definitions. If a broken SROM is detected a card may
** use this inक्रमmation to help figure out what to करो. This is a
** "stab in the dark" and so far क्रम SMC9332's only.
*/
अटल c_अक्षर srom_repair_info[][100] = अणु
    अणु0x00,0x1e,0x00,0x00,0x00,0x08,             /* SMC9332 */
     0x1f,0x01,0x8f,0x01,0x00,0x01,0x00,0x02,
     0x01,0x00,0x00,0x78,0xe0,0x01,0x00,0x50,
     0x00,0x18,पूर्ण
पूर्ण;


#अगर_घोषित DE4X5_DEBUG
अटल पूर्णांक de4x5_debug = DE4X5_DEBUG;
#अन्यथा
/*अटल पूर्णांक de4x5_debug = (DEBUG_MII | DEBUG_SROM | DEBUG_PCICFG | DEBUG_MEDIA | DEBUG_VERSION);*/
अटल पूर्णांक de4x5_debug = (DEBUG_MEDIA | DEBUG_VERSION);
#पूर्ण_अगर

/*
** Allow per adapter set up. For modules this is simply a command line
** parameter, e.g.:
** insmod de4x5 args='eth1:fdx autosense=BNC eth0:autosense=100Mb'.
**
** For a compiled in driver, place e.g.
**     #घोषणा DE4X5_PARM "eth0:fdx autosense=AUI eth2:autosense=TP"
** here
*/
#अगर_घोषित DE4X5_PARM
अटल अक्षर *args = DE4X5_PARM;
#अन्यथा
अटल अक्षर *args;
#पूर्ण_अगर

काष्ठा parameters अणु
    bool fdx;
    पूर्णांक स्वतःsense;
पूर्ण;

#घोषणा DE4X5_AUTOSENSE_MS 250      /* msec स्वतःsense tick (DE500) */

#घोषणा DE4X5_NDA 0xffe0            /* No Device (I/O) Address */

/*
** Ethernet PROM defines
*/
#घोषणा PROBE_LENGTH    32
#घोषणा ETH_PROM_SIG    0xAA5500FFUL

/*
** Ethernet Info
*/
#घोषणा PKT_BUF_SZ	1536            /* Buffer size क्रम each Tx/Rx buffer */
#घोषणा IEEE802_3_SZ    1518            /* Packet + CRC */
#घोषणा MAX_PKT_SZ   	1514            /* Maximum ethernet packet length */
#घोषणा MAX_DAT_SZ   	1500            /* Maximum ethernet data length */
#घोषणा MIN_DAT_SZ   	1               /* Minimum ethernet data length */
#घोषणा PKT_HDR_LEN     14              /* Addresses and data length info */
#घोषणा FAKE_FRAME_LEN  (MAX_PKT_SZ + 1)
#घोषणा QUEUE_PKT_TIMEOUT (3*HZ)        /* 3 second समयout */


/*
** EISA bus defines
*/
#घोषणा DE4X5_EISA_IO_PORTS   0x0c00    /* I/O port base address, slot 0 */
#घोषणा DE4X5_EISA_TOTAL_SIZE 0x100     /* I/O address extent */

#घोषणा EISA_ALLOWED_IRQ_LIST  अणु5, 9, 10, 11पूर्ण

#घोषणा DE4X5_SIGNATURE अणु"DE425","DE434","DE435","DE450","DE500"पूर्ण
#घोषणा DE4X5_NAME_LENGTH 8

अटल c_अक्षर *de4x5_signatures[] = DE4X5_SIGNATURE;

/*
** Ethernet PROM defines क्रम DC21040
*/
#घोषणा PROBE_LENGTH    32
#घोषणा ETH_PROM_SIG    0xAA5500FFUL

/*
** PCI Bus defines
*/
#घोषणा PCI_MAX_BUS_NUM      8
#घोषणा DE4X5_PCI_TOTAL_SIZE 0x80       /* I/O address extent */
#घोषणा DE4X5_CLASS_CODE     0x00020000 /* Network controller, Ethernet */

/*
** Memory Alignment. Each descriptor is 4 दीर्घwords दीर्घ. To क्रमce a
** particular alignment on the TX descriptor, adjust DESC_SKIP_LEN and
** DESC_ALIGN. ALIGN aligns the start address of the निजी memory area
** and hence the RX descriptor ring's first entry.
*/
#घोषणा DE4X5_ALIGN4      ((u_दीर्घ)4 - 1)     /* 1 दीर्घword align */
#घोषणा DE4X5_ALIGN8      ((u_दीर्घ)8 - 1)     /* 2 दीर्घword align */
#घोषणा DE4X5_ALIGN16     ((u_दीर्घ)16 - 1)    /* 4 दीर्घword align */
#घोषणा DE4X5_ALIGN32     ((u_दीर्घ)32 - 1)    /* 8 दीर्घword align */
#घोषणा DE4X5_ALIGN64     ((u_दीर्घ)64 - 1)    /* 16 दीर्घword align */
#घोषणा DE4X5_ALIGN128    ((u_दीर्घ)128 - 1)   /* 32 दीर्घword align */

#घोषणा DE4X5_ALIGN         DE4X5_ALIGN32           /* Keep the DC21040 happy... */
#घोषणा DE4X5_CACHE_ALIGN   CAL_16LONG
#घोषणा DESC_SKIP_LEN DSL_0             /* Must agree with DESC_ALIGN */
/*#घोषणा DESC_ALIGN    u32 dummy[4];  / * Must agree with DESC_SKIP_LEN */
#घोषणा DESC_ALIGN

#अगर_अघोषित DEC_ONLY                        /* See README.de4x5 क्रम using this */
अटल पूर्णांक dec_only;
#अन्यथा
अटल पूर्णांक dec_only = 1;
#पूर्ण_अगर

/*
** DE4X5 IRQ ENABLE/DISABLE
*/
#घोषणा ENABLE_IRQs अणु \
    imr |= lp->irq_en;\
    outl(imr, DE4X5_IMR);               /* Enable the IRQs */\
पूर्ण

#घोषणा DISABLE_IRQs अणु\
    imr = inl(DE4X5_IMR);\
    imr &= ~lp->irq_en;\
    outl(imr, DE4X5_IMR);               /* Disable the IRQs */\
पूर्ण

#घोषणा UNMASK_IRQs अणु\
    imr |= lp->irq_mask;\
    outl(imr, DE4X5_IMR);               /* Unmask the IRQs */\
पूर्ण

#घोषणा MASK_IRQs अणु\
    imr = inl(DE4X5_IMR);\
    imr &= ~lp->irq_mask;\
    outl(imr, DE4X5_IMR);               /* Mask the IRQs */\
पूर्ण

/*
** DE4X5 START/STOP
*/
#घोषणा START_DE4X5 अणु\
    omr = inl(DE4X5_OMR);\
    omr |= OMR_ST | OMR_SR;\
    outl(omr, DE4X5_OMR);               /* Enable the TX and/or RX */\
पूर्ण

#घोषणा STOP_DE4X5 अणु\
    omr = inl(DE4X5_OMR);\
    omr &= ~(OMR_ST|OMR_SR);\
    outl(omr, DE4X5_OMR);               /* Disable the TX and/or RX */ \
पूर्ण

/*
** DE4X5 SIA RESET
*/
#घोषणा RESET_SIA outl(0, DE4X5_SICR);  /* Reset SIA connectivity regs */

/*
** DE500 AUTOSENSE TIMER INTERVAL (MILLISECS)
*/
#घोषणा DE4X5_AUTOSENSE_MS  250

/*
** SROM Structure
*/
काष्ठा de4x5_srom अणु
    अक्षर sub_venकरोr_id[2];
    अक्षर sub_प्रणाली_id[2];
    अक्षर reserved[12];
    अक्षर id_block_crc;
    अक्षर reserved2;
    अक्षर version;
    अक्षर num_controllers;
    अक्षर ieee_addr[6];
    अक्षर info[100];
    लघु chksum;
पूर्ण;
#घोषणा SUB_VENDOR_ID 0x500a

/*
** DE4X5 Descriptors. Make sure that all the RX buffers are contiguous
** and have sizes of both a घातer of 2 and a multiple of 4.
** A size of 256 bytes क्रम each buffer could be chosen because over 90% of
** all packets in our network are <256 bytes दीर्घ and 64 दीर्घword alignment
** is possible. 1536 showed better 'ttcp' perक्रमmance. Take your pick. 32 TX
** descriptors are needed क्रम machines with an ALPHA CPU.
*/
#घोषणा NUM_RX_DESC 8                   /* Number of RX descriptors   */
#घोषणा NUM_TX_DESC 32                  /* Number of TX descriptors   */
#घोषणा RX_BUFF_SZ  1536                /* Power of 2 क्रम kदो_स्मृति and */
                                        /* Multiple of 4 क्रम DC21040  */
                                        /* Allows 512 byte alignment  */
काष्ठा de4x5_desc अणु
    अस्थिर __le32 status;
    __le32 des1;
    __le32 buf;
    __le32 next;
    DESC_ALIGN
पूर्ण;

/*
** The DE4X5 निजी काष्ठाure
*/
#घोषणा DE4X5_PKT_STAT_SZ 16
#घोषणा DE4X5_PKT_BIN_SZ  128            /* Should be >=100 unless you
                                            increase DE4X5_PKT_STAT_SZ */

काष्ठा pkt_stats अणु
	u_पूर्णांक bins[DE4X5_PKT_STAT_SZ];      /* Private stats counters       */
	u_पूर्णांक unicast;
	u_पूर्णांक multicast;
	u_पूर्णांक broadcast;
	u_पूर्णांक excessive_collisions;
	u_पूर्णांक tx_underruns;
	u_पूर्णांक excessive_underruns;
	u_पूर्णांक rx_runt_frames;
	u_पूर्णांक rx_collision;
	u_पूर्णांक rx_dribble;
	u_पूर्णांक rx_overflow;
पूर्ण;

काष्ठा de4x5_निजी अणु
    अक्षर adapter_name[80];                  /* Adapter name                 */
    u_दीर्घ पूर्णांकerrupt;                       /* Aligned ISR flag             */
    काष्ठा de4x5_desc *rx_ring;		    /* RX descriptor ring           */
    काष्ठा de4x5_desc *tx_ring;		    /* TX descriptor ring           */
    काष्ठा sk_buff *tx_skb[NUM_TX_DESC];    /* TX skb क्रम मुक्तing when sent */
    काष्ठा sk_buff *rx_skb[NUM_RX_DESC];    /* RX skb's                     */
    पूर्णांक rx_new, rx_old;                     /* RX descriptor ring poपूर्णांकers  */
    पूर्णांक tx_new, tx_old;                     /* TX descriptor ring poपूर्णांकers  */
    अक्षर setup_frame[SETUP_FRAME_LEN];      /* Holds MCA and PA info.       */
    अक्षर frame[64];                         /* Min sized packet क्रम loopback*/
    spinlock_t lock;                        /* Adapter specअगरic spinlock    */
    काष्ठा net_device_stats stats;          /* Public stats                 */
    काष्ठा pkt_stats pktStats;	            /* Private stats counters	    */
    अक्षर rxRingSize;
    अक्षर txRingSize;
    पूर्णांक  bus;                               /* EISA or PCI                  */
    पूर्णांक  bus_num;                           /* PCI Bus number               */
    पूर्णांक  device;                            /* Device number on PCI bus     */
    पूर्णांक  state;                             /* Adapter OPENED or CLOSED     */
    पूर्णांक  chipset;                           /* DC21040, DC21041 or DC21140  */
    s32  irq_mask;                          /* Interrupt Mask (Enable) bits */
    s32  irq_en;                            /* Summary पूर्णांकerrupt bits       */
    पूर्णांक  media;                             /* Media (eg TP), mode (eg 100B)*/
    पूर्णांक  c_media;                           /* Remember the last media conn */
    bool fdx;                               /* media full duplex flag       */
    पूर्णांक  linkOK;                            /* Link is OK                   */
    पूर्णांक  स्वतःsense;                         /* Allow/disallow स्वतःsensing   */
    bool tx_enable;                         /* Enable descriptor polling    */
    पूर्णांक  setup_f;                           /* Setup frame filtering type   */
    पूर्णांक  local_state;                       /* State within a 'media' state */
    काष्ठा mii_phy phy[DE4X5_MAX_PHY];      /* List of attached PHY devices */
    काष्ठा sia_phy sia;                     /* SIA PHY Inक्रमmation          */
    पूर्णांक  active;                            /* Index to active PHY device   */
    पूर्णांक  mii_cnt;                           /* Number of attached PHY's     */
    पूर्णांक  समयout;                           /* Scheduling counter           */
    काष्ठा समयr_list समयr;                /* Timer info क्रम kernel        */
    पूर्णांक पंचांगp;                                /* Temporary global per card    */
    काष्ठा अणु
	u_दीर्घ lock;                        /* Lock the cache accesses      */
	s32 csr0;                           /* Saved Bus Mode Register      */
	s32 csr6;                           /* Saved Operating Mode Reg.    */
	s32 csr7;                           /* Saved IRQ Mask Register      */
	s32 gep;                            /* Saved General Purpose Reg.   */
	s32 gepc;                           /* Control info क्रम GEP         */
	s32 csr13;                          /* Saved SIA Connectivity Reg.  */
	s32 csr14;                          /* Saved SIA TX/RX Register     */
	s32 csr15;                          /* Saved SIA General Register   */
	पूर्णांक save_cnt;                       /* Flag अगर state alपढ़ोy saved  */
	काष्ठा sk_buff_head queue;          /* Save the (re-ordered) skb's  */
    पूर्ण cache;
    काष्ठा de4x5_srom srom;                 /* A copy of the SROM           */
    पूर्णांक cfrv;				    /* Card CFRV copy */
    पूर्णांक rx_ovf;                             /* Check क्रम 'RX overflow' tag  */
    bool useSROM;                           /* For non-DEC card use SROM    */
    bool useMII;                            /* Infoblock using the MII      */
    पूर्णांक asBitValid;                         /* Autosense bits in GEP?       */
    पूर्णांक asPolarity;                         /* 0 => निश्चितed high           */
    पूर्णांक asBit;                              /* Autosense bit number in GEP  */
    पूर्णांक defMedium;                          /* SROM शेष medium          */
    पूर्णांक tcount;                             /* Last infoblock number        */
    पूर्णांक infoblock_init;                     /* Initialised this infoblock?  */
    पूर्णांक infoleaf_offset;                    /* SROM infoleaf क्रम controller */
    s32 infoblock_csr6;                     /* csr6 value in SROM infoblock */
    पूर्णांक infoblock_media;                    /* infoblock media              */
    पूर्णांक (*infoleaf_fn)(काष्ठा net_device *);    /* Poपूर्णांकer to infoleaf function */
    u_अक्षर *rst;                            /* Poपूर्णांकer to Type 5 reset info */
    u_अक्षर  ibn;                            /* Infoblock number             */
    काष्ठा parameters params;               /* Command line/ #घोषणाd params */
    काष्ठा device *gendev;	            /* Generic device */
    dma_addr_t dma_rings;		    /* DMA handle क्रम rings	    */
    पूर्णांक dma_size;			    /* Size of the DMA area	    */
    अक्षर *rx_bufs;			    /* rx bufs on alpha, sparc, ... */
पूर्ण;

/*
** To get around certain poxy cards that करोn't provide an SROM
** क्रम the second and more DECchip, I have to key off the first
** chip's address. I'll assume there's not a bad SROM अगरf:
**
**      o the chipset is the same
**      o the bus number is the same and > 0
**      o the sum of all the वापसed hw address bytes is 0 or 0x5fa
**
** Also have to save the irq क्रम those cards whose hardware designers
** can't follow the PCI to PCI Bridge Architecture spec.
*/
अटल काष्ठा अणु
    पूर्णांक chipset;
    पूर्णांक bus;
    पूर्णांक irq;
    u_अक्षर addr[ETH_ALEN];
पूर्ण last = अणु0,पूर्ण;

/*
** The transmit ring full condition is described by the tx_old and tx_new
** poपूर्णांकers by:
**    tx_old            = tx_new    Empty ring
**    tx_old            = tx_new+1  Full ring
**    tx_old+txRingSize = tx_new+1  Full ring  (wrapped condition)
*/
#घोषणा TX_BUFFS_AVAIL ((lp->tx_old<=lp->tx_new)?\
			lp->tx_old+lp->txRingSize-lp->tx_new-1:\
			lp->tx_old               -lp->tx_new-1)

#घोषणा TX_PKT_PENDING (lp->tx_old != lp->tx_new)

/*
** Public Functions
*/
अटल पूर्णांक     de4x5_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t de4x5_queue_pkt(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev);
अटल irqवापस_t de4x5_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक     de4x5_बंद(काष्ठा net_device *dev);
अटल काष्ठा  net_device_stats *de4x5_get_stats(काष्ठा net_device *dev);
अटल व्योम    de4x5_local_stats(काष्ठा net_device *dev, अक्षर *buf, पूर्णांक pkt_len);
अटल व्योम    set_multicast_list(काष्ठा net_device *dev);
अटल पूर्णांक     de4x5_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);

/*
** Private functions
*/
अटल पूर्णांक     de4x5_hw_init(काष्ठा net_device *dev, u_दीर्घ iobase, काष्ठा device *gendev);
अटल पूर्णांक     de4x5_init(काष्ठा net_device *dev);
अटल पूर्णांक     de4x5_sw_reset(काष्ठा net_device *dev);
अटल पूर्णांक     de4x5_rx(काष्ठा net_device *dev);
अटल पूर्णांक     de4x5_tx(काष्ठा net_device *dev);
अटल व्योम    de4x5_ast(काष्ठा समयr_list *t);
अटल पूर्णांक     de4x5_txur(काष्ठा net_device *dev);
अटल पूर्णांक     de4x5_rx_ovfc(काष्ठा net_device *dev);

अटल पूर्णांक     स्वतःconf_media(काष्ठा net_device *dev);
अटल व्योम    create_packet(काष्ठा net_device *dev, अक्षर *frame, पूर्णांक len);
अटल व्योम    load_packet(काष्ठा net_device *dev, अक्षर *buf, u32 flags, काष्ठा sk_buff *skb);
अटल पूर्णांक     dc21040_स्वतःconf(काष्ठा net_device *dev);
अटल पूर्णांक     dc21041_स्वतःconf(काष्ठा net_device *dev);
अटल पूर्णांक     dc21140m_स्वतःconf(काष्ठा net_device *dev);
अटल पूर्णांक     dc2114x_स्वतःconf(काष्ठा net_device *dev);
अटल पूर्णांक     srom_स्वतःconf(काष्ठा net_device *dev);
अटल पूर्णांक     de4x5_suspect_state(काष्ठा net_device *dev, पूर्णांक समयout, पूर्णांक prev_state, पूर्णांक (*fn)(काष्ठा net_device *, पूर्णांक), पूर्णांक (*asfn)(काष्ठा net_device *));
अटल पूर्णांक     dc21040_state(काष्ठा net_device *dev, पूर्णांक csr13, पूर्णांक csr14, पूर्णांक csr15, पूर्णांक समयout, पूर्णांक next_state, पूर्णांक suspect_state, पूर्णांक (*fn)(काष्ठा net_device *, पूर्णांक));
अटल पूर्णांक     test_media(काष्ठा net_device *dev, s32 irqs, s32 irq_mask, s32 csr13, s32 csr14, s32 csr15, s32 msec);
अटल पूर्णांक     test_क्रम_100Mb(काष्ठा net_device *dev, पूर्णांक msec);
अटल पूर्णांक     रुको_क्रम_link(काष्ठा net_device *dev);
अटल पूर्णांक     test_mii_reg(काष्ठा net_device *dev, पूर्णांक reg, पूर्णांक mask, bool pol, दीर्घ msec);
अटल पूर्णांक     is_spd_100(काष्ठा net_device *dev);
अटल पूर्णांक     is_100_up(काष्ठा net_device *dev);
अटल पूर्णांक     is_10_up(काष्ठा net_device *dev);
अटल पूर्णांक     is_anc_capable(काष्ठा net_device *dev);
अटल पूर्णांक     ping_media(काष्ठा net_device *dev, पूर्णांक msec);
अटल काष्ठा sk_buff *de4x5_alloc_rx_buff(काष्ठा net_device *dev, पूर्णांक index, पूर्णांक len);
अटल व्योम    de4x5_मुक्त_rx_buffs(काष्ठा net_device *dev);
अटल व्योम    de4x5_मुक्त_tx_buffs(काष्ठा net_device *dev);
अटल व्योम    de4x5_save_skbs(काष्ठा net_device *dev);
अटल व्योम    de4x5_rst_desc_ring(काष्ठा net_device *dev);
अटल व्योम    de4x5_cache_state(काष्ठा net_device *dev, पूर्णांक flag);
अटल व्योम    de4x5_put_cache(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
अटल व्योम    de4x5_putb_cache(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
अटल काष्ठा  sk_buff *de4x5_get_cache(काष्ठा net_device *dev);
अटल व्योम    de4x5_setup_पूर्णांकr(काष्ठा net_device *dev);
अटल व्योम    de4x5_init_connection(काष्ठा net_device *dev);
अटल पूर्णांक     de4x5_reset_phy(काष्ठा net_device *dev);
अटल व्योम    reset_init_sia(काष्ठा net_device *dev, s32 sicr, s32 strr, s32 sigr);
अटल पूर्णांक     test_ans(काष्ठा net_device *dev, s32 irqs, s32 irq_mask, s32 msec);
अटल पूर्णांक     test_tp(काष्ठा net_device *dev, s32 msec);
अटल पूर्णांक     EISA_signature(अक्षर *name, काष्ठा device *device);
अटल व्योम    PCI_signature(अक्षर *name, काष्ठा de4x5_निजी *lp);
अटल व्योम    DevicePresent(काष्ठा net_device *dev, u_दीर्घ iobase);
अटल व्योम    enet_addr_rst(u_दीर्घ aprom_addr);
अटल पूर्णांक     de4x5_bad_srom(काष्ठा de4x5_निजी *lp);
अटल लघु   srom_rd(u_दीर्घ address, u_अक्षर offset);
अटल व्योम    srom_latch(u_पूर्णांक command, u_दीर्घ address);
अटल व्योम    srom_command(u_पूर्णांक command, u_दीर्घ address);
अटल व्योम    srom_address(u_पूर्णांक command, u_दीर्घ address, u_अक्षर offset);
अटल लघु   srom_data(u_पूर्णांक command, u_दीर्घ address);
/*अटल व्योम    srom_busy(u_पूर्णांक command, u_दीर्घ address);*/
अटल व्योम    sendto_srom(u_पूर्णांक command, u_दीर्घ addr);
अटल पूर्णांक     getfrom_srom(u_दीर्घ addr);
अटल पूर्णांक     srom_map_media(काष्ठा net_device *dev);
अटल पूर्णांक     srom_infoleaf_info(काष्ठा net_device *dev);
अटल व्योम    srom_init(काष्ठा net_device *dev);
अटल व्योम    srom_exec(काष्ठा net_device *dev, u_अक्षर *p);
अटल पूर्णांक     mii_rd(u_अक्षर phyreg, u_अक्षर phyaddr, u_दीर्घ ioaddr);
अटल व्योम    mii_wr(पूर्णांक data, u_अक्षर phyreg, u_अक्षर phyaddr, u_दीर्घ ioaddr);
अटल पूर्णांक     mii_rdata(u_दीर्घ ioaddr);
अटल व्योम    mii_wdata(पूर्णांक data, पूर्णांक len, u_दीर्घ ioaddr);
अटल व्योम    mii_ta(u_दीर्घ rw, u_दीर्घ ioaddr);
अटल पूर्णांक     mii_swap(पूर्णांक data, पूर्णांक len);
अटल व्योम    mii_address(u_अक्षर addr, u_दीर्घ ioaddr);
अटल व्योम    sendto_mii(u32 command, पूर्णांक data, u_दीर्घ ioaddr);
अटल पूर्णांक     getfrom_mii(u32 command, u_दीर्घ ioaddr);
अटल पूर्णांक     mii_get_oui(u_अक्षर phyaddr, u_दीर्घ ioaddr);
अटल पूर्णांक     mii_get_phy(काष्ठा net_device *dev);
अटल व्योम    SetMulticastFilter(काष्ठा net_device *dev);
अटल पूर्णांक     get_hw_addr(काष्ठा net_device *dev);
अटल व्योम    srom_repair(काष्ठा net_device *dev, पूर्णांक card);
अटल पूर्णांक     test_bad_enet(काष्ठा net_device *dev, पूर्णांक status);
अटल पूर्णांक     an_exception(काष्ठा de4x5_निजी *lp);
अटल अक्षर    *build_setup_frame(काष्ठा net_device *dev, पूर्णांक mode);
अटल व्योम    disable_ast(काष्ठा net_device *dev);
अटल दीर्घ    de4x5_चयन_mac_port(काष्ठा net_device *dev);
अटल पूर्णांक     gep_rd(काष्ठा net_device *dev);
अटल व्योम    gep_wr(s32 data, काष्ठा net_device *dev);
अटल व्योम    yawn(काष्ठा net_device *dev, पूर्णांक state);
अटल व्योम    de4x5_parse_params(काष्ठा net_device *dev);
अटल व्योम    de4x5_dbg_खोलो(काष्ठा net_device *dev);
अटल व्योम    de4x5_dbg_mii(काष्ठा net_device *dev, पूर्णांक k);
अटल व्योम    de4x5_dbg_media(काष्ठा net_device *dev);
अटल व्योम    de4x5_dbg_srom(काष्ठा de4x5_srom *p);
अटल व्योम    de4x5_dbg_rx(काष्ठा sk_buff *skb, पूर्णांक len);
अटल पूर्णांक     dc21041_infoleaf(काष्ठा net_device *dev);
अटल पूर्णांक     dc21140_infoleaf(काष्ठा net_device *dev);
अटल पूर्णांक     dc21142_infoleaf(काष्ठा net_device *dev);
अटल पूर्णांक     dc21143_infoleaf(काष्ठा net_device *dev);
अटल पूर्णांक     type0_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p);
अटल पूर्णांक     type1_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p);
अटल पूर्णांक     type2_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p);
अटल पूर्णांक     type3_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p);
अटल पूर्णांक     type4_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p);
अटल पूर्णांक     type5_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p);
अटल पूर्णांक     compact_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p);

/*
** Note now that module स्वतःprobing is allowed under EISA and PCI. The
** IRQ lines will not be स्वतः-detected; instead I'll rely on the BIOSes
** to "do the right thing".
*/

अटल पूर्णांक io=0x0;/* EDIT THIS LINE FOR YOUR CONFIGURATION IF NEEDED        */

module_param_hw(io, पूर्णांक, ioport, 0);
module_param(de4x5_debug, पूर्णांक, 0);
module_param(dec_only, पूर्णांक, 0);
module_param(args, अक्षरp, 0);

MODULE_PARM_DESC(io, "de4x5 I/O base address");
MODULE_PARM_DESC(de4x5_debug, "de4x5 debug mask");
MODULE_PARM_DESC(dec_only, "de4x5 probe only for Digital boards (0-1)");
MODULE_PARM_DESC(args, "de4x5 full duplex and media type settings; see de4x5.c for details");
MODULE_LICENSE("GPL");

/*
** List the SROM infoleaf functions and chipsets
*/
काष्ठा InfoLeaf अणु
    पूर्णांक chipset;
    पूर्णांक (*fn)(काष्ठा net_device *);
पूर्ण;
अटल काष्ठा InfoLeaf infoleaf_array[] = अणु
    अणुDC21041, dc21041_infoleafपूर्ण,
    अणुDC21140, dc21140_infoleafपूर्ण,
    अणुDC21142, dc21142_infoleafपूर्ण,
    अणुDC21143, dc21143_infoleafपूर्ण
पूर्ण;
#घोषणा INFOLEAF_SIZE ARRAY_SIZE(infoleaf_array)

/*
** List the SROM info block functions
*/
अटल पूर्णांक (*dc_infoblock[])(काष्ठा net_device *dev, u_अक्षर, u_अक्षर *) = अणु
    type0_infoblock,
    type1_infoblock,
    type2_infoblock,
    type3_infoblock,
    type4_infoblock,
    type5_infoblock,
    compact_infoblock
पूर्ण;

#घोषणा COMPACT (ARRAY_SIZE(dc_infoblock) - 1)

/*
** Miscellaneous defines...
*/
#घोषणा RESET_DE4X5 अणु\
    पूर्णांक i;\
    i=inl(DE4X5_BMR);\
    mdelay(1);\
    outl(i | BMR_SWR, DE4X5_BMR);\
    mdelay(1);\
    outl(i, DE4X5_BMR);\
    mdelay(1);\
    क्रम (i=0;i<5;i++) अणुinl(DE4X5_BMR); mdelay(1);पूर्ण\
    mdelay(1);\
पूर्ण

#घोषणा PHY_HARD_RESET अणु\
    outl(GEP_HRST, DE4X5_GEP);           /* Hard RESET the PHY dev. */\
    mdelay(1);                           /* Assert क्रम 1ms */\
    outl(0x00, DE4X5_GEP);\
    mdelay(2);                           /* Wait क्रम 2ms */\
पूर्ण

अटल स्थिर काष्ठा net_device_ops de4x5_netdev_ops = अणु
    .nकरो_खोलो		= de4x5_खोलो,
    .nकरो_stop		= de4x5_बंद,
    .nकरो_start_xmit	= de4x5_queue_pkt,
    .nकरो_get_stats	= de4x5_get_stats,
    .nकरो_set_rx_mode	= set_multicast_list,
    .nकरो_करो_ioctl	= de4x5_ioctl,
    .nकरो_set_mac_address= eth_mac_addr,
    .nकरो_validate_addr	= eth_validate_addr,
पूर्ण;


अटल पूर्णांक
de4x5_hw_init(काष्ठा net_device *dev, u_दीर्घ iobase, काष्ठा device *gendev)
अणु
    अक्षर name[DE4X5_NAME_LENGTH + 1];
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    काष्ठा pci_dev *pdev = शून्य;
    पूर्णांक i, status=0;

    dev_set_drvdata(gendev, dev);

    /* Ensure we're not sleeping */
    अगर (lp->bus == EISA) अणु
	outb(WAKEUP, PCI_CFPM);
    पूर्ण अन्यथा अणु
	pdev = to_pci_dev (gendev);
	pci_ग_लिखो_config_byte(pdev, PCI_CFDA_PSM, WAKEUP);
    पूर्ण
    mdelay(10);

    RESET_DE4X5;

    अगर ((inl(DE4X5_STS) & (STS_TS | STS_RS)) != 0) अणु
	वापस -ENXIO;                       /* Hardware could not reset */
    पूर्ण

    /*
    ** Now find out what kind of DC21040/DC21041/DC21140 board we have.
    */
    lp->useSROM = false;
    अगर (lp->bus == PCI) अणु
	PCI_signature(name, lp);
    पूर्ण अन्यथा अणु
	EISA_signature(name, gendev);
    पूर्ण

    अगर (*name == '\0') अणु                     /* Not found a board signature */
	वापस -ENXIO;
    पूर्ण

    dev->base_addr = iobase;
    prपूर्णांकk ("%s: %s at 0x%04lx", dev_name(gendev), name, iobase);

    status = get_hw_addr(dev);
    prपूर्णांकk(", h/w address %pM\n", dev->dev_addr);

    अगर (status != 0) अणु
	prपूर्णांकk("      which has an Ethernet PROM CRC error.\n");
	वापस -ENXIO;
    पूर्ण अन्यथा अणु
	skb_queue_head_init(&lp->cache.queue);
	lp->cache.gepc = GEP_INIT;
	lp->asBit = GEP_SLNK;
	lp->asPolarity = GEP_SLNK;
	lp->asBitValid = ~0;
	lp->समयout = -1;
	lp->gendev = gendev;
	spin_lock_init(&lp->lock);
	समयr_setup(&lp->समयr, de4x5_ast, 0);
	de4x5_parse_params(dev);

	/*
	** Choose correct स्वतःsensing in हाल someone messed up
	*/
        lp->स्वतःsense = lp->params.स्वतःsense;
        अगर (lp->chipset != DC21140) अणु
            अगर ((lp->chipset==DC21040) && (lp->params.स्वतःsense&TP_NW)) अणु
                lp->params.स्वतःsense = TP;
            पूर्ण
            अगर ((lp->chipset==DC21041) && (lp->params.स्वतःsense&BNC_AUI)) अणु
                lp->params.स्वतःsense = BNC;
            पूर्ण
        पूर्ण
	lp->fdx = lp->params.fdx;
	प्र_लिखो(lp->adapter_name,"%s (%s)", name, dev_name(gendev));

	lp->dma_size = (NUM_RX_DESC + NUM_TX_DESC) * माप(काष्ठा de4x5_desc);
#अगर defined(__alpha__) || defined(__घातerpc__) || defined(CONFIG_SPARC) || defined(DE4X5_DO_MEMCPY)
	lp->dma_size += RX_BUFF_SZ * NUM_RX_DESC + DE4X5_ALIGN;
#पूर्ण_अगर
	lp->rx_ring = dma_alloc_coherent(gendev, lp->dma_size,
					 &lp->dma_rings, GFP_ATOMIC);
	अगर (lp->rx_ring == शून्य) अणु
	    वापस -ENOMEM;
	पूर्ण

	lp->tx_ring = lp->rx_ring + NUM_RX_DESC;

	/*
	** Set up the RX descriptor ring (Intels)
	** Allocate contiguous receive buffers, दीर्घ word aligned (Alphas)
	*/
#अगर !defined(__alpha__) && !defined(__घातerpc__) && !defined(CONFIG_SPARC) && !defined(DE4X5_DO_MEMCPY)
	क्रम (i=0; i<NUM_RX_DESC; i++) अणु
	    lp->rx_ring[i].status = 0;
	    lp->rx_ring[i].des1 = cpu_to_le32(RX_BUFF_SZ);
	    lp->rx_ring[i].buf = 0;
	    lp->rx_ring[i].next = 0;
	    lp->rx_skb[i] = (काष्ठा sk_buff *) 1;     /* Dummy entry */
	पूर्ण

#अन्यथा
	अणु
		dma_addr_t dma_rx_bufs;

		dma_rx_bufs = lp->dma_rings + (NUM_RX_DESC + NUM_TX_DESC)
		      	* माप(काष्ठा de4x5_desc);
		dma_rx_bufs = (dma_rx_bufs + DE4X5_ALIGN) & ~DE4X5_ALIGN;
		lp->rx_bufs = (अक्षर *)(((दीर्घ)(lp->rx_ring + NUM_RX_DESC
		      	+ NUM_TX_DESC) + DE4X5_ALIGN) & ~DE4X5_ALIGN);
		क्रम (i=0; i<NUM_RX_DESC; i++) अणु
	    		lp->rx_ring[i].status = 0;
	    		lp->rx_ring[i].des1 = cpu_to_le32(RX_BUFF_SZ);
	    		lp->rx_ring[i].buf =
				cpu_to_le32(dma_rx_bufs+i*RX_BUFF_SZ);
	    		lp->rx_ring[i].next = 0;
	    		lp->rx_skb[i] = (काष्ठा sk_buff *) 1; /* Dummy entry */
		पूर्ण

	पूर्ण
#पूर्ण_अगर

	barrier();

	lp->rxRingSize = NUM_RX_DESC;
	lp->txRingSize = NUM_TX_DESC;

	/* Write the end of list marker to the descriptor lists */
	lp->rx_ring[lp->rxRingSize - 1].des1 |= cpu_to_le32(RD_RER);
	lp->tx_ring[lp->txRingSize - 1].des1 |= cpu_to_le32(TD_TER);

	/* Tell the adapter where the TX/RX rings are located. */
	outl(lp->dma_rings, DE4X5_RRBA);
	outl(lp->dma_rings + NUM_RX_DESC * माप(काष्ठा de4x5_desc),
	     DE4X5_TRBA);

	/* Initialise the IRQ mask and Enable/Disable */
	lp->irq_mask = IMR_RIM | IMR_TIM | IMR_TUM | IMR_UNM;
	lp->irq_en   = IMR_NIM | IMR_AIM;

	/* Create a loopback packet frame क्रम later media probing */
	create_packet(dev, lp->frame, माप(lp->frame));

	/* Check अगर the RX overflow bug needs testing क्रम */
	i = lp->cfrv & 0x000000fe;
	अगर ((lp->chipset == DC21140) && (i == 0x20)) अणु
	    lp->rx_ovf = 1;
	पूर्ण

	/* Initialise the SROM poपूर्णांकers अगर possible */
	अगर (lp->useSROM) अणु
	    lp->state = INITIALISED;
	    अगर (srom_infoleaf_info(dev)) अणु
	        dma_मुक्त_coherent (gendev, lp->dma_size,
			       lp->rx_ring, lp->dma_rings);
		वापस -ENXIO;
	    पूर्ण
	    srom_init(dev);
	पूर्ण

	lp->state = CLOSED;

	/*
	** Check क्रम an MII पूर्णांकerface
	*/
	अगर ((lp->chipset != DC21040) && (lp->chipset != DC21041)) अणु
	    mii_get_phy(dev);
	पूर्ण

	prपूर्णांकk("      and requires IRQ%d (provided by %s).\n", dev->irq,
	       ((lp->bus == PCI) ? "PCI BIOS" : "EISA CNFG"));
    पूर्ण

    अगर (de4x5_debug & DEBUG_VERSION) अणु
	prपूर्णांकk(version);
    पूर्ण

    /* The DE4X5-specअगरic entries in the device काष्ठाure. */
    SET_NETDEV_DEV(dev, gendev);
    dev->netdev_ops = &de4x5_netdev_ops;
    dev->mem_start = 0;

    /* Fill in the generic fields of the device काष्ठाure. */
    अगर ((status = रेजिस्टर_netdev (dev))) अणु
	    dma_मुक्त_coherent (gendev, lp->dma_size,
			       lp->rx_ring, lp->dma_rings);
	    वापस status;
    पूर्ण

    /* Let the adapter sleep to save घातer */
    yawn(dev, SLEEP);

    वापस status;
पूर्ण


अटल पूर्णांक
de4x5_खोलो(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक i, status = 0;
    s32 omr;

    /* Allocate the RX buffers */
    क्रम (i=0; i<lp->rxRingSize; i++) अणु
	अगर (de4x5_alloc_rx_buff(dev, i, 0) == शून्य) अणु
	    de4x5_मुक्त_rx_buffs(dev);
	    वापस -EAGAIN;
	पूर्ण
    पूर्ण

    /*
    ** Wake up the adapter
    */
    yawn(dev, WAKEUP);

    /*
    ** Re-initialize the DE4X5...
    */
    status = de4x5_init(dev);
    spin_lock_init(&lp->lock);
    lp->state = OPEN;
    de4x5_dbg_खोलो(dev);

    अगर (request_irq(dev->irq, de4x5_पूर्णांकerrupt, IRQF_SHARED,
		                                     lp->adapter_name, dev)) अणु
	prपूर्णांकk("de4x5_open(): Requested IRQ%d is busy - attempting FAST/SHARE...", dev->irq);
	अगर (request_irq(dev->irq, de4x5_पूर्णांकerrupt, IRQF_SHARED,
			                             lp->adapter_name, dev)) अणु
	    prपूर्णांकk("\n              Cannot get IRQ- reconfigure your hardware.\n");
	    disable_ast(dev);
	    de4x5_मुक्त_rx_buffs(dev);
	    de4x5_मुक्त_tx_buffs(dev);
	    yawn(dev, SLEEP);
	    lp->state = CLOSED;
	    वापस -EAGAIN;
	पूर्ण अन्यथा अणु
	    prपूर्णांकk("\n              Succeeded, but you should reconfigure your hardware to avoid this.\n");
	    prपूर्णांकk("WARNING: there may be IRQ related problems in heavily loaded systems.\n");
	पूर्ण
    पूर्ण

    lp->पूर्णांकerrupt = UNMASK_INTERRUPTS;
    netअगर_trans_update(dev); /* prevent tx समयout */

    START_DE4X5;

    de4x5_setup_पूर्णांकr(dev);

    अगर (de4x5_debug & DEBUG_OPEN) अणु
	prपूर्णांकk("\tsts:  0x%08x\n", inl(DE4X5_STS));
	prपूर्णांकk("\tbmr:  0x%08x\n", inl(DE4X5_BMR));
	prपूर्णांकk("\timr:  0x%08x\n", inl(DE4X5_IMR));
	prपूर्णांकk("\tomr:  0x%08x\n", inl(DE4X5_OMR));
	prपूर्णांकk("\tsisr: 0x%08x\n", inl(DE4X5_SISR));
	prपूर्णांकk("\tsicr: 0x%08x\n", inl(DE4X5_SICR));
	prपूर्णांकk("\tstrr: 0x%08x\n", inl(DE4X5_STRR));
	prपूर्णांकk("\tsigr: 0x%08x\n", inl(DE4X5_SIGR));
    पूर्ण

    वापस status;
पूर्ण

/*
** Initialize the DE4X5 operating conditions. NB: a chip problem with the
** DC21140 requires using perfect filtering mode क्रम that chip. Since I can't
** see why I'd want > 14 multicast addresses, I have changed all chips to use
** the perfect filtering mode. Keep the DMA burst length at 8: there seems
** to be data corruption problems अगर it is larger (UDP errors seen from a
** ttcp source).
*/
अटल पूर्णांक
de4x5_init(काष्ठा net_device *dev)
अणु
    /* Lock out other processes whilst setting up the hardware */
    netअगर_stop_queue(dev);

    de4x5_sw_reset(dev);

    /* Autoconfigure the connected port */
    स्वतःconf_media(dev);

    वापस 0;
पूर्ण

अटल पूर्णांक
de4x5_sw_reset(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक i, j, status = 0;
    s32 bmr, omr;

    /* Select the MII or SRL port now and RESET the MAC */
    अगर (!lp->useSROM) अणु
	अगर (lp->phy[lp->active].id != 0) अणु
	    lp->infoblock_csr6 = OMR_SDP | OMR_PS | OMR_HBD;
	पूर्ण अन्यथा अणु
	    lp->infoblock_csr6 = OMR_SDP | OMR_TTM;
	पूर्ण
	de4x5_चयन_mac_port(dev);
    पूर्ण

    /*
    ** Set the programmable burst length to 8 दीर्घwords क्रम all the DC21140
    ** Fasternet chips and 4 दीर्घwords क्रम all others: DMA errors result
    ** without these values. Cache align 16 दीर्घ.
    */
    bmr = (lp->chipset==DC21140 ? PBL_8 : PBL_4) | DESC_SKIP_LEN | DE4X5_CACHE_ALIGN;
    bmr |= ((lp->chipset & ~0x00ff)==DC2114x ? BMR_RML : 0);
    outl(bmr, DE4X5_BMR);

    omr = inl(DE4X5_OMR) & ~OMR_PR;             /* Turn off promiscuous mode */
    अगर (lp->chipset == DC21140) अणु
	omr |= (OMR_SDP | OMR_SB);
    पूर्ण
    lp->setup_f = PERFECT;
    outl(lp->dma_rings, DE4X5_RRBA);
    outl(lp->dma_rings + NUM_RX_DESC * माप(काष्ठा de4x5_desc),
	 DE4X5_TRBA);

    lp->rx_new = lp->rx_old = 0;
    lp->tx_new = lp->tx_old = 0;

    क्रम (i = 0; i < lp->rxRingSize; i++) अणु
	lp->rx_ring[i].status = cpu_to_le32(R_OWN);
    पूर्ण

    क्रम (i = 0; i < lp->txRingSize; i++) अणु
	lp->tx_ring[i].status = cpu_to_le32(0);
    पूर्ण

    barrier();

    /* Build the setup frame depending on filtering mode */
    SetMulticastFilter(dev);

    load_packet(dev, lp->setup_frame, PERFECT_F|TD_SET|SETUP_FRAME_LEN, (काष्ठा sk_buff *)1);
    outl(omr|OMR_ST, DE4X5_OMR);

    /* Poll क्रम setup frame completion (adapter पूर्णांकerrupts are disabled now) */

    क्रम (j=0, i=0;(i<500) && (j==0);i++) अणु       /* Up to 500ms delay */
	mdelay(1);
	अगर ((s32)le32_to_cpu(lp->tx_ring[lp->tx_new].status) >= 0) j=1;
    पूर्ण
    outl(omr, DE4X5_OMR);                        /* Stop everything! */

    अगर (j == 0) अणु
	prपूर्णांकk("%s: Setup frame timed out, status %08x\n", dev->name,
	       inl(DE4X5_STS));
	status = -EIO;
    पूर्ण

    lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;
    lp->tx_old = lp->tx_new;

    वापस status;
पूर्ण

/*
** Writes a socket buffer address to the next available transmit descriptor.
*/
अटल netdev_tx_t
de4x5_queue_pkt(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    u_दीर्घ flags = 0;

    netअगर_stop_queue(dev);
    अगर (!lp->tx_enable)                   /* Cannot send क्रम now */
		जाओ tx_err;

    /*
    ** Clean out the TX ring asynchronously to पूर्णांकerrupts - someबार the
    ** पूर्णांकerrupts are lost by delayed descriptor status updates relative to
    ** the irq निश्चितion, especially with a busy PCI bus.
    */
    spin_lock_irqsave(&lp->lock, flags);
    de4x5_tx(dev);
    spin_unlock_irqrestore(&lp->lock, flags);

    /* Test अगर cache is alपढ़ोy locked - requeue skb अगर so */
    अगर (test_and_set_bit(0, (व्योम *)&lp->cache.lock) && !lp->पूर्णांकerrupt)
		जाओ tx_err;

    /* Transmit descriptor ring full or stale skb */
    अगर (netअगर_queue_stopped(dev) || (u_दीर्घ) lp->tx_skb[lp->tx_new] > 1) अणु
	अगर (lp->पूर्णांकerrupt) अणु
	    de4x5_putb_cache(dev, skb);          /* Requeue the buffer */
	पूर्ण अन्यथा अणु
	    de4x5_put_cache(dev, skb);
	पूर्ण
	अगर (de4x5_debug & DEBUG_TX) अणु
	    prपूर्णांकk("%s: transmit busy, lost media or stale skb found:\n  STS:%08x\n  tbusy:%d\n  IMR:%08x\n  OMR:%08x\n Stale skb: %s\n",dev->name, inl(DE4X5_STS), netअगर_queue_stopped(dev), inl(DE4X5_IMR), inl(DE4X5_OMR), ((u_दीर्घ) lp->tx_skb[lp->tx_new] > 1) ? "YES" : "NO");
	पूर्ण
    पूर्ण अन्यथा अगर (skb->len > 0) अणु
	/* If we alपढ़ोy have stuff queued locally, use that first */
	अगर (!skb_queue_empty(&lp->cache.queue) && !lp->पूर्णांकerrupt) अणु
	    de4x5_put_cache(dev, skb);
	    skb = de4x5_get_cache(dev);
	पूर्ण

	जबतक (skb && !netअगर_queue_stopped(dev) &&
	       (u_दीर्घ) lp->tx_skb[lp->tx_new] <= 1) अणु
	    spin_lock_irqsave(&lp->lock, flags);
	    netअगर_stop_queue(dev);
	    load_packet(dev, skb->data, TD_IC | TD_LS | TD_FS | skb->len, skb);
 	    lp->stats.tx_bytes += skb->len;
	    outl(POLL_DEMAND, DE4X5_TPD);/* Start the TX */

	    lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;

	    अगर (TX_BUFFS_AVAIL) अणु
		netअगर_start_queue(dev);         /* Another pkt may be queued */
	    पूर्ण
	    skb = de4x5_get_cache(dev);
	    spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण
	अगर (skb) de4x5_putb_cache(dev, skb);
    पूर्ण

    lp->cache.lock = 0;

    वापस NETDEV_TX_OK;
tx_err:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/*
** The DE4X5 पूर्णांकerrupt handler.
**
** I/O Read/Writes through पूर्णांकermediate PCI bridges are never 'posted',
** so that the निश्चितed पूर्णांकerrupt always has some real data to work with -
** अगर these I/O accesses are ever changed to memory accesses, ensure the
** STS ग_लिखो is पढ़ो immediately to complete the transaction अगर the adapter
** is not on bus 0. Lost पूर्णांकerrupts can still occur when the PCI bus load
** is high and descriptor status bits cannot be set beक्रमe the associated
** पूर्णांकerrupt is निश्चितed and this routine entered.
*/
अटल irqवापस_t
de4x5_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = dev_id;
    काष्ठा de4x5_निजी *lp;
    s32 imr, omr, sts, limit;
    u_दीर्घ iobase;
    अचिन्हित पूर्णांक handled = 0;

    lp = netdev_priv(dev);
    spin_lock(&lp->lock);
    iobase = dev->base_addr;

    DISABLE_IRQs;                        /* Ensure non re-entrancy */

    अगर (test_and_set_bit(MASK_INTERRUPTS, (व्योम*) &lp->पूर्णांकerrupt))
	prपूर्णांकk("%s: Re-entering the interrupt handler.\n", dev->name);

    synchronize_irq(dev->irq);

    क्रम (limit=0; limit<8; limit++) अणु
	sts = inl(DE4X5_STS);            /* Read IRQ status */
	outl(sts, DE4X5_STS);            /* Reset the board पूर्णांकerrupts */

	अगर (!(sts & lp->irq_mask)) अवरोध;/* All करोne */
	handled = 1;

	अगर (sts & (STS_RI | STS_RU))     /* Rx पूर्णांकerrupt (packet[s] arrived) */
	  de4x5_rx(dev);

	अगर (sts & (STS_TI | STS_TU))     /* Tx पूर्णांकerrupt (packet sent) */
	  de4x5_tx(dev);

	अगर (sts & STS_LNF) अणु             /* TP Link has failed */
	    lp->irq_mask &= ~IMR_LFM;
	पूर्ण

	अगर (sts & STS_UNF) अणु             /* Transmit underrun */
	    de4x5_txur(dev);
	पूर्ण

	अगर (sts & STS_SE) अणु              /* Bus Error */
	    STOP_DE4X5;
	    prपूर्णांकk("%s: Fatal bus error occurred, sts=%#8x, device stopped.\n",
		   dev->name, sts);
	    spin_unlock(&lp->lock);
	    वापस IRQ_HANDLED;
	पूर्ण
    पूर्ण

    /* Load the TX ring with any locally stored packets */
    अगर (!test_and_set_bit(0, (व्योम *)&lp->cache.lock)) अणु
	जबतक (!skb_queue_empty(&lp->cache.queue) && !netअगर_queue_stopped(dev) && lp->tx_enable) अणु
	    de4x5_queue_pkt(de4x5_get_cache(dev), dev);
	पूर्ण
	lp->cache.lock = 0;
    पूर्ण

    lp->पूर्णांकerrupt = UNMASK_INTERRUPTS;
    ENABLE_IRQs;
    spin_unlock(&lp->lock);

    वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक
de4x5_rx(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक entry;
    s32 status;

    क्रम (entry=lp->rx_new; (s32)le32_to_cpu(lp->rx_ring[entry].status)>=0;
	                                                    entry=lp->rx_new) अणु
	status = (s32)le32_to_cpu(lp->rx_ring[entry].status);

	अगर (lp->rx_ovf) अणु
	    अगर (inl(DE4X5_MFC) & MFC_FOCM) अणु
		de4x5_rx_ovfc(dev);
		अवरोध;
	    पूर्ण
	पूर्ण

	अगर (status & RD_FS) अणु                 /* Remember the start of frame */
	    lp->rx_old = entry;
	पूर्ण

	अगर (status & RD_LS) अणु                 /* Valid frame status */
	    अगर (lp->tx_enable) lp->linkOK++;
	    अगर (status & RD_ES) अणु	      /* There was an error. */
		lp->stats.rx_errors++;        /* Update the error stats. */
		अगर (status & (RD_RF | RD_TL)) lp->stats.rx_frame_errors++;
		अगर (status & RD_CE)           lp->stats.rx_crc_errors++;
		अगर (status & RD_OF)           lp->stats.rx_fअगरo_errors++;
		अगर (status & RD_TL)           lp->stats.rx_length_errors++;
		अगर (status & RD_RF)           lp->pktStats.rx_runt_frames++;
		अगर (status & RD_CS)           lp->pktStats.rx_collision++;
		अगर (status & RD_DB)           lp->pktStats.rx_dribble++;
		अगर (status & RD_OF)           lp->pktStats.rx_overflow++;
	    पूर्ण अन्यथा अणु                          /* A valid frame received */
		काष्ठा sk_buff *skb;
		लघु pkt_len = (लघु)(le32_to_cpu(lp->rx_ring[entry].status)
					                            >> 16) - 4;

		अगर ((skb = de4x5_alloc_rx_buff(dev, entry, pkt_len)) == शून्य) अणु
		    prपूर्णांकk("%s: Insufficient memory; nuking packet.\n",
			                                            dev->name);
		    lp->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
		    de4x5_dbg_rx(skb, pkt_len);

		    /* Push up the protocol stack */
		    skb->protocol=eth_type_trans(skb,dev);
		    de4x5_local_stats(dev, skb->data, pkt_len);
		    netअगर_rx(skb);

		    /* Update stats */
		    lp->stats.rx_packets++;
 		    lp->stats.rx_bytes += pkt_len;
		पूर्ण
	    पूर्ण

	    /* Change buffer ownership क्रम this frame, back to the adapter */
	    क्रम (;lp->rx_old!=entry;lp->rx_old=(lp->rx_old + 1)%lp->rxRingSize) अणु
		lp->rx_ring[lp->rx_old].status = cpu_to_le32(R_OWN);
		barrier();
	    पूर्ण
	    lp->rx_ring[entry].status = cpu_to_le32(R_OWN);
	    barrier();
	पूर्ण

	/*
	** Update entry inक्रमmation
	*/
	lp->rx_new = (lp->rx_new + 1) % lp->rxRingSize;
    पूर्ण

    वापस 0;
पूर्ण

अटल अंतरभूत व्योम
de4x5_मुक्त_tx_buff(काष्ठा de4x5_निजी *lp, पूर्णांक entry)
अणु
    dma_unmap_single(lp->gendev, le32_to_cpu(lp->tx_ring[entry].buf),
		     le32_to_cpu(lp->tx_ring[entry].des1) & TD_TBS1,
		     DMA_TO_DEVICE);
    अगर ((u_दीर्घ) lp->tx_skb[entry] > 1)
	dev_kमुक्त_skb_irq(lp->tx_skb[entry]);
    lp->tx_skb[entry] = शून्य;
पूर्ण

/*
** Buffer sent - check क्रम TX buffer errors.
*/
अटल पूर्णांक
de4x5_tx(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक entry;
    s32 status;

    क्रम (entry = lp->tx_old; entry != lp->tx_new; entry = lp->tx_old) अणु
	status = (s32)le32_to_cpu(lp->tx_ring[entry].status);
	अगर (status < 0) अणु                     /* Buffer not sent yet */
	    अवरोध;
	पूर्ण अन्यथा अगर (status != 0x7fffffff) अणु    /* Not setup frame */
	    अगर (status & TD_ES) अणु             /* An error happened */
		lp->stats.tx_errors++;
		अगर (status & TD_NC) lp->stats.tx_carrier_errors++;
		अगर (status & TD_LC) lp->stats.tx_winकरोw_errors++;
		अगर (status & TD_UF) lp->stats.tx_fअगरo_errors++;
		अगर (status & TD_EC) lp->pktStats.excessive_collisions++;
		अगर (status & TD_DE) lp->stats.tx_पातed_errors++;

		अगर (TX_PKT_PENDING) अणु
		    outl(POLL_DEMAND, DE4X5_TPD);/* Restart a stalled TX */
		पूर्ण
	    पूर्ण अन्यथा अणु                      /* Packet sent */
		lp->stats.tx_packets++;
		अगर (lp->tx_enable) lp->linkOK++;
	    पूर्ण
	    /* Update the collision counter */
	    lp->stats.collisions += ((status & TD_EC) ? 16 :
				                      ((status & TD_CC) >> 3));

	    /* Free the buffer. */
	    अगर (lp->tx_skb[entry] != शून्य)
	    	de4x5_मुक्त_tx_buff(lp, entry);
	पूर्ण

	/* Update all the poपूर्णांकers */
	lp->tx_old = (lp->tx_old + 1) % lp->txRingSize;
    पूर्ण

    /* Any resources available? */
    अगर (TX_BUFFS_AVAIL && netअगर_queue_stopped(dev)) अणु
	अगर (lp->पूर्णांकerrupt)
	    netअगर_wake_queue(dev);
	अन्यथा
	    netअगर_start_queue(dev);
    पूर्ण

    वापस 0;
पूर्ण

अटल व्योम
de4x5_ast(काष्ठा समयr_list *t)
अणु
	काष्ठा de4x5_निजी *lp = from_समयr(lp, t, समयr);
	काष्ठा net_device *dev = dev_get_drvdata(lp->gendev);
	पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;
	पूर्णांक dt;

	अगर (lp->useSROM)
		next_tick = srom_स्वतःconf(dev);
	अन्यथा अगर (lp->chipset == DC21140)
		next_tick = dc21140m_स्वतःconf(dev);
	अन्यथा अगर (lp->chipset == DC21041)
		next_tick = dc21041_स्वतःconf(dev);
	अन्यथा अगर (lp->chipset == DC21040)
		next_tick = dc21040_स्वतःconf(dev);
	lp->linkOK = 0;

	dt = (next_tick * HZ) / 1000;

	अगर (!dt)
		dt = 1;

	mod_समयr(&lp->समयr, jअगरfies + dt);
पूर्ण

अटल पूर्णांक
de4x5_txur(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक omr;

    omr = inl(DE4X5_OMR);
    अगर (!(omr & OMR_SF) || (lp->chipset==DC21041) || (lp->chipset==DC21040)) अणु
	omr &= ~(OMR_ST|OMR_SR);
	outl(omr, DE4X5_OMR);
	जबतक (inl(DE4X5_STS) & STS_TS);
	अगर ((omr & OMR_TR) < OMR_TR) अणु
	    omr += 0x4000;
	पूर्ण अन्यथा अणु
	    omr |= OMR_SF;
	पूर्ण
	outl(omr | OMR_ST | OMR_SR, DE4X5_OMR);
    पूर्ण

    वापस 0;
पूर्ण

अटल पूर्णांक
de4x5_rx_ovfc(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक omr;

    omr = inl(DE4X5_OMR);
    outl(omr & ~OMR_SR, DE4X5_OMR);
    जबतक (inl(DE4X5_STS) & STS_RS);

    क्रम (; (s32)le32_to_cpu(lp->rx_ring[lp->rx_new].status)>=0;) अणु
	lp->rx_ring[lp->rx_new].status = cpu_to_le32(R_OWN);
	lp->rx_new = (lp->rx_new + 1) % lp->rxRingSize;
    पूर्ण

    outl(omr, DE4X5_OMR);

    वापस 0;
पूर्ण

अटल पूर्णांक
de4x5_बंद(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 imr, omr;

    disable_ast(dev);

    netअगर_stop_queue(dev);

    अगर (de4x5_debug & DEBUG_CLOSE) अणु
	prपूर्णांकk("%s: Shutting down ethercard, status was %8.8x.\n",
	       dev->name, inl(DE4X5_STS));
    पूर्ण

    /*
    ** We stop the DE4X5 here... mask पूर्णांकerrupts and stop TX & RX
    */
    DISABLE_IRQs;
    STOP_DE4X5;

    /* Free the associated irq */
    मुक्त_irq(dev->irq, dev);
    lp->state = CLOSED;

    /* Free any socket buffers */
    de4x5_मुक्त_rx_buffs(dev);
    de4x5_मुक्त_tx_buffs(dev);

    /* Put the adapter to sleep to save घातer */
    yawn(dev, SLEEP);

    वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *
de4x5_get_stats(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    lp->stats.rx_missed_errors = (पूर्णांक)(inl(DE4X5_MFC) & (MFC_OVFL | MFC_CNTR));

    वापस &lp->stats;
पूर्ण

अटल व्योम
de4x5_local_stats(काष्ठा net_device *dev, अक्षर *buf, पूर्णांक pkt_len)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक i;

    क्रम (i=1; i<DE4X5_PKT_STAT_SZ-1; i++) अणु
        अगर (pkt_len < (i*DE4X5_PKT_BIN_SZ)) अणु
	    lp->pktStats.bins[i]++;
	    i = DE4X5_PKT_STAT_SZ;
	पूर्ण
    पूर्ण
    अगर (is_multicast_ether_addr(buf)) अणु
        अगर (is_broadcast_ether_addr(buf)) अणु
	    lp->pktStats.broadcast++;
	पूर्ण अन्यथा अणु
	    lp->pktStats.multicast++;
	पूर्ण
    पूर्ण अन्यथा अगर (ether_addr_equal(buf, dev->dev_addr)) अणु
        lp->pktStats.unicast++;
    पूर्ण

    lp->pktStats.bins[0]++;       /* Duplicates stats.rx_packets */
    अगर (lp->pktStats.bins[0] == 0) अणु /* Reset counters */
        स_रखो((अक्षर *)&lp->pktStats, 0, माप(lp->pktStats));
    पूर्ण
पूर्ण

/*
** Removes the TD_IC flag from previous descriptor to improve TX perक्रमmance.
** If the flag is changed on a descriptor that is being पढ़ो by the hardware,
** I assume PCI transaction ordering will mean you are either successful or
** just miss निश्चितing the change to the hardware. Anyway you're messing with
** a descriptor you करोn't own, but this shouldn't समाप्त the chip provided
** the descriptor रेजिस्टर is पढ़ो only to the hardware.
*/
अटल व्योम
load_packet(काष्ठा net_device *dev, अक्षर *buf, u32 flags, काष्ठा sk_buff *skb)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक entry = (lp->tx_new ? lp->tx_new-1 : lp->txRingSize-1);
    dma_addr_t buf_dma = dma_map_single(lp->gendev, buf, flags & TD_TBS1, DMA_TO_DEVICE);

    lp->tx_ring[lp->tx_new].buf = cpu_to_le32(buf_dma);
    lp->tx_ring[lp->tx_new].des1 &= cpu_to_le32(TD_TER);
    lp->tx_ring[lp->tx_new].des1 |= cpu_to_le32(flags);
    lp->tx_skb[lp->tx_new] = skb;
    lp->tx_ring[entry].des1 &= cpu_to_le32(~TD_IC);
    barrier();

    lp->tx_ring[lp->tx_new].status = cpu_to_le32(T_OWN);
    barrier();
पूर्ण

/*
** Set or clear the multicast filter क्रम this adaptor.
*/
अटल व्योम
set_multicast_list(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    /* First, द्विगुन check that the adapter is खोलो */
    अगर (lp->state == OPEN) अणु
	अगर (dev->flags & IFF_PROMISC) अणु         /* set promiscuous mode */
	    u32 omr;
	    omr = inl(DE4X5_OMR);
	    omr |= OMR_PR;
	    outl(omr, DE4X5_OMR);
	पूर्ण अन्यथा अणु
	    SetMulticastFilter(dev);
	    load_packet(dev, lp->setup_frame, TD_IC | PERFECT_F | TD_SET |
			                                SETUP_FRAME_LEN, (काष्ठा sk_buff *)1);

	    lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;
	    outl(POLL_DEMAND, DE4X5_TPD);       /* Start the TX */
	    netअगर_trans_update(dev); /* prevent tx समयout */
	पूर्ण
    पूर्ण
पूर्ण

/*
** Calculate the hash code and update the logical address filter
** from a list of ethernet multicast addresses.
** Little endian crc one liner from Matt Thomas, DEC.
*/
अटल व्योम
SetMulticastFilter(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    काष्ठा netdev_hw_addr *ha;
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक i, bit, byte;
    u16 hashcode;
    u32 omr, crc;
    अक्षर *pa;
    अचिन्हित अक्षर *addrs;

    omr = inl(DE4X5_OMR);
    omr &= ~(OMR_PR | OMR_PM);
    pa = build_setup_frame(dev, ALL);        /* Build the basic frame */

    अगर ((dev->flags & IFF_ALLMULTI) || (netdev_mc_count(dev) > 14)) अणु
	omr |= OMR_PM;                       /* Pass all multicasts */
    पूर्ण अन्यथा अगर (lp->setup_f == HASH_PERF) अणु   /* Hash Filtering */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		crc = ether_crc_le(ETH_ALEN, ha->addr);
		hashcode = crc & DE4X5_HASH_BITS;  /* hashcode is 9 LSb of CRC */

		byte = hashcode >> 3;        /* bit[3-8] -> byte in filter */
		bit = 1 << (hashcode & 0x07);/* bit[0-2] -> bit in byte */

		byte <<= 1;                  /* calc offset पूर्णांकo setup frame */
		अगर (byte & 0x02) अणु
		    byte -= 1;
		पूर्ण
		lp->setup_frame[byte] |= bit;
	पूर्ण
    पूर्ण अन्यथा अणु                                 /* Perfect filtering */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
	    addrs = ha->addr;
	    क्रम (i=0; i<ETH_ALEN; i++) अणु
		*(pa + (i&1)) = *addrs++;
		अगर (i & 0x01) pa += 4;
	    पूर्ण
	पूर्ण
    पूर्ण
    outl(omr, DE4X5_OMR);
पूर्ण

#अगर_घोषित CONFIG_EISA

अटल u_अक्षर de4x5_irq[] = EISA_ALLOWED_IRQ_LIST;

अटल पूर्णांक de4x5_eisa_probe(काष्ठा device *gendev)
अणु
	काष्ठा eisa_device *edev;
	u_दीर्घ iobase;
	u_अक्षर irq, regval;
	u_लघु venकरोr;
	u32 cfid;
	पूर्णांक status, device;
	काष्ठा net_device *dev;
	काष्ठा de4x5_निजी *lp;

	edev = to_eisa_device (gendev);
	iobase = edev->base_addr;

	अगर (!request_region (iobase, DE4X5_EISA_TOTAL_SIZE, "de4x5"))
		वापस -EBUSY;

	अगर (!request_region (iobase + DE4X5_EISA_IO_PORTS,
			     DE4X5_EISA_TOTAL_SIZE, "de4x5")) अणु
		status = -EBUSY;
		जाओ release_reg_1;
	पूर्ण

	अगर (!(dev = alloc_etherdev (माप (काष्ठा de4x5_निजी)))) अणु
		status = -ENOMEM;
		जाओ release_reg_2;
	पूर्ण
	lp = netdev_priv(dev);

	cfid = (u32) inl(PCI_CFID);
	lp->cfrv = (u_लघु) inl(PCI_CFRV);
	device = (cfid >> 8) & 0x00ffff00;
	venकरोr = (u_लघु) cfid;

	/* Read the EISA Configuration Registers */
	regval = inb(EISA_REG0) & (ER0_INTL | ER0_INTT);
#अगर_घोषित CONFIG_ALPHA
	/* Looks like the Jensen firmware (rev 2.2) करोesn't really
	 * care about the EISA configuration, and thus करोesn't
	 * configure the PLX bridge properly. Oh well... Simply mimic
	 * the EISA config file to sort it out. */

	/* EISA REG1: Assert DecChip 21040 HW Reset */
	outb (ER1_IAM | 1, EISA_REG1);
	mdelay (1);

        /* EISA REG1: Deनिश्चित DecChip 21040 HW Reset */
	outb (ER1_IAM, EISA_REG1);
	mdelay (1);

	/* EISA REG3: R/W Burst Transfer Enable */
	outb (ER3_BWE | ER3_BRE, EISA_REG3);

	/* 32_bit slave/master, Preempt Time=23 bclks, Unlatched Interrupt */
	outb (ER0_BSW | ER0_BMW | ER0_EPT | regval, EISA_REG0);
#पूर्ण_अगर
	irq = de4x5_irq[(regval >> 1) & 0x03];

	अगर (is_DC2114x) अणु
	    device = ((lp->cfrv & CFRV_RN) < DC2114x_BRK ? DC21142 : DC21143);
	पूर्ण
	lp->chipset = device;
	lp->bus = EISA;

	/* Write the PCI Configuration Registers */
	outl(PCI_COMMAND_IO | PCI_COMMAND_MASTER, PCI_CFCS);
	outl(0x00006000, PCI_CFLT);
	outl(iobase, PCI_CBIO);

	DevicePresent(dev, EISA_APROM);

	dev->irq = irq;

	अगर (!(status = de4x5_hw_init (dev, iobase, gendev))) अणु
		वापस 0;
	पूर्ण

	मुक्त_netdev (dev);
 release_reg_2:
	release_region (iobase + DE4X5_EISA_IO_PORTS, DE4X5_EISA_TOTAL_SIZE);
 release_reg_1:
	release_region (iobase, DE4X5_EISA_TOTAL_SIZE);

	वापस status;
पूर्ण

अटल पूर्णांक de4x5_eisa_हटाओ(काष्ठा device *device)
अणु
	काष्ठा net_device *dev;
	u_दीर्घ iobase;

	dev = dev_get_drvdata(device);
	iobase = dev->base_addr;

	unरेजिस्टर_netdev (dev);
	मुक्त_netdev (dev);
	release_region (iobase + DE4X5_EISA_IO_PORTS, DE4X5_EISA_TOTAL_SIZE);
	release_region (iobase, DE4X5_EISA_TOTAL_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा eisa_device_id de4x5_eisa_ids[] = अणु
        अणु "DEC4250", 0 पूर्ण,	/* 0 is the board name index... */
        अणु "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(eisa, de4x5_eisa_ids);

अटल काष्ठा eisa_driver de4x5_eisa_driver = अणु
        .id_table = de4x5_eisa_ids,
        .driver   = अणु
                .name    = "de4x5",
                .probe   = de4x5_eisa_probe,
		.हटाओ  = de4x5_eisa_हटाओ,
        पूर्ण
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI

/*
** This function searches the current bus (which is >0) क्रम a DECchip with an
** SROM, so that in multiport cards that have one SROM shared between multiple
** DECchips, we can find the base SROM irrespective of the BIOS scan direction.
** For single port cards this is a समय waster...
*/
अटल व्योम
srom_search(काष्ठा net_device *dev, काष्ठा pci_dev *pdev)
अणु
    u_अक्षर pb;
    u_लघु venकरोr, status;
    u_पूर्णांक irq = 0, device;
    u_दीर्घ iobase = 0;                     /* Clear upper 32 bits in Alphas */
    पूर्णांक i, j;
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    काष्ठा pci_dev *this_dev;

    list_क्रम_each_entry(this_dev, &pdev->bus->devices, bus_list) अणु
	venकरोr = this_dev->venकरोr;
	device = this_dev->device << 8;
	अगर (!(is_DC21040 || is_DC21041 || is_DC21140 || is_DC2114x)) जारी;

	/* Get the chip configuration revision रेजिस्टर */
	pb = this_dev->bus->number;

	/* Set the device number inक्रमmation */
	lp->device = PCI_SLOT(this_dev->devfn);
	lp->bus_num = pb;

	/* Set the chipset inक्रमmation */
	अगर (is_DC2114x) अणु
	    device = ((this_dev->revision & CFRV_RN) < DC2114x_BRK
		      ? DC21142 : DC21143);
	पूर्ण
	lp->chipset = device;

	/* Get the board I/O address (64 bits on sparc64) */
	iobase = pci_resource_start(this_dev, 0);

	/* Fetch the IRQ to be used */
	irq = this_dev->irq;
	अगर ((irq == 0) || (irq == 0xff) || ((पूर्णांक)irq == -1)) जारी;

	/* Check अगर I/O accesses are enabled */
	pci_पढ़ो_config_word(this_dev, PCI_COMMAND, &status);
	अगर (!(status & PCI_COMMAND_IO)) जारी;

	/* Search क्रम a valid SROM attached to this DECchip */
	DevicePresent(dev, DE4X5_APROM);
	क्रम (j=0, i=0; i<ETH_ALEN; i++) अणु
	    j += (u_अक्षर) *((u_अक्षर *)&lp->srom + SROM_HWADD + i);
	पूर्ण
	अगर (j != 0 && j != 6 * 0xff) अणु
	    last.chipset = device;
	    last.bus = pb;
	    last.irq = irq;
	    क्रम (i=0; i<ETH_ALEN; i++) अणु
		last.addr[i] = (u_अक्षर)*((u_अक्षर *)&lp->srom + SROM_HWADD + i);
	    पूर्ण
	    वापस;
	पूर्ण
    पूर्ण
पूर्ण

/*
** PCI bus I/O device probe
** NB: PCI I/O accesses and Bus Mastering are enabled by the PCI BIOS, not
** the driver. Some PCI BIOS's, pre V2.1, need the slot + features to be
** enabled by the user first in the set up utility. Hence we just check क्रम
** enabled features and silently ignore the card अगर they're not.
**
** STOP PRESS: Some BIOS's __require__ the driver to enable the bus mastering
** bit. Here, check क्रम I/O accesses and then set BM. If you put the card in
** a non BM slot, you're on your own (and complain to the PC venकरोr that your
** PC करोesn't conक्रमm to the PCI standard)!
**
** This function is only compatible with the *latest* 2.1.x kernels. For 2.0.x
** kernels use the V0.535[n] drivers.
*/

अटल पूर्णांक de4x5_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	u_अक्षर pb, pbus = 0, dev_num, dnum = 0, समयr;
	u_लघु venकरोr, status;
	u_पूर्णांक irq = 0, device;
	u_दीर्घ iobase = 0;	/* Clear upper 32 bits in Alphas */
	पूर्णांक error;
	काष्ठा net_device *dev;
	काष्ठा de4x5_निजी *lp;

	dev_num = PCI_SLOT(pdev->devfn);
	pb = pdev->bus->number;

	अगर (io) अणु /* probe a single PCI device */
		pbus = (u_लघु)(io >> 8);
		dnum = (u_लघु)(io & 0xff);
		अगर ((pbus != pb) || (dnum != dev_num))
			वापस -ENODEV;
	पूर्ण

	venकरोr = pdev->venकरोr;
	device = pdev->device << 8;
	अगर (!(is_DC21040 || is_DC21041 || is_DC21140 || is_DC2114x))
		वापस -ENODEV;

	/* Ok, the device seems to be क्रम us. */
	अगर ((error = pci_enable_device (pdev)))
		वापस error;

	अगर (!(dev = alloc_etherdev (माप (काष्ठा de4x5_निजी)))) अणु
		error = -ENOMEM;
		जाओ disable_dev;
	पूर्ण

	lp = netdev_priv(dev);
	lp->bus = PCI;
	lp->bus_num = 0;

	/* Search क्रम an SROM on this bus */
	अगर (lp->bus_num != pb) अणु
	    lp->bus_num = pb;
	    srom_search(dev, pdev);
	पूर्ण

	/* Get the chip configuration revision रेजिस्टर */
	lp->cfrv = pdev->revision;

	/* Set the device number inक्रमmation */
	lp->device = dev_num;
	lp->bus_num = pb;

	/* Set the chipset inक्रमmation */
	अगर (is_DC2114x) अणु
	    device = ((lp->cfrv & CFRV_RN) < DC2114x_BRK ? DC21142 : DC21143);
	पूर्ण
	lp->chipset = device;

	/* Get the board I/O address (64 bits on sparc64) */
	iobase = pci_resource_start(pdev, 0);

	/* Fetch the IRQ to be used */
	irq = pdev->irq;
	अगर ((irq == 0) || (irq == 0xff) || ((पूर्णांक)irq == -1)) अणु
		error = -ENODEV;
		जाओ मुक्त_dev;
	पूर्ण

	/* Check अगर I/O accesses and Bus Mastering are enabled */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &status);
#अगर_घोषित __घातerpc__
	अगर (!(status & PCI_COMMAND_IO)) अणु
	    status |= PCI_COMMAND_IO;
	    pci_ग_लिखो_config_word(pdev, PCI_COMMAND, status);
	    pci_पढ़ो_config_word(pdev, PCI_COMMAND, &status);
	पूर्ण
#पूर्ण_अगर /* __घातerpc__ */
	अगर (!(status & PCI_COMMAND_IO)) अणु
		error = -ENODEV;
		जाओ मुक्त_dev;
	पूर्ण

	अगर (!(status & PCI_COMMAND_MASTER)) अणु
	    status |= PCI_COMMAND_MASTER;
	    pci_ग_लिखो_config_word(pdev, PCI_COMMAND, status);
	    pci_पढ़ो_config_word(pdev, PCI_COMMAND, &status);
	पूर्ण
	अगर (!(status & PCI_COMMAND_MASTER)) अणु
		error = -ENODEV;
		जाओ मुक्त_dev;
	पूर्ण

	/* Check the latency समयr क्रम values >= 0x60 */
	pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &समयr);
	अगर (समयr < 0x60) अणु
	    pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x60);
	पूर्ण

	DevicePresent(dev, DE4X5_APROM);

	अगर (!request_region (iobase, DE4X5_PCI_TOTAL_SIZE, "de4x5")) अणु
		error = -EBUSY;
		जाओ मुक्त_dev;
	पूर्ण

	dev->irq = irq;

	अगर ((error = de4x5_hw_init(dev, iobase, &pdev->dev))) अणु
		जाओ release;
	पूर्ण

	वापस 0;

 release:
	release_region (iobase, DE4X5_PCI_TOTAL_SIZE);
 मुक्त_dev:
	मुक्त_netdev (dev);
 disable_dev:
	pci_disable_device (pdev);
	वापस error;
पूर्ण

अटल व्योम de4x5_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev;
	u_दीर्घ iobase;

	dev = pci_get_drvdata(pdev);
	iobase = dev->base_addr;

	unरेजिस्टर_netdev (dev);
	मुक्त_netdev (dev);
	release_region (iobase, DE4X5_PCI_TOTAL_SIZE);
	pci_disable_device (pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id de4x5_pci_tbl[] = अणु
        अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TULIP,
          PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
        अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TULIP_PLUS,
          PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 पूर्ण,
        अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TULIP_FAST,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2 पूर्ण,
        अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_21142,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 3 पूर्ण,
        अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver de4x5_pci_driver = अणु
        .name           = "de4x5",
        .id_table       = de4x5_pci_tbl,
        .probe          = de4x5_pci_probe,
	.हटाओ         = de4x5_pci_हटाओ,
पूर्ण;

#पूर्ण_अगर

/*
** Auto configure the media here rather than setting the port at compile
** समय. This routine is called by de4x5_init() and when a loss of media is
** detected (excessive collisions, loss of carrier, no carrier or link fail
** [TP] or no recent receive activity) to check whether the user has been
** sneaky and changed the port on us.
*/
अटल पूर्णांक
स्वतःconf_media(काष्ठा net_device *dev)
अणु
	काष्ठा de4x5_निजी *lp = netdev_priv(dev);
	u_दीर्घ iobase = dev->base_addr;

	disable_ast(dev);

	lp->c_media = AUTO;                     /* Bogus last media */
	inl(DE4X5_MFC);                         /* Zero the lost frames counter */
	lp->media = INIT;
	lp->tcount = 0;

	de4x5_ast(&lp->समयr);

	वापस lp->media;
पूर्ण

/*
** Autoconfigure the media when using the DC21040. AUI cannot be distinguished
** from BNC as the port has a jumper to set thick or thin wire. When set क्रम
** BNC, the BNC port will indicate activity अगर it's not terminated correctly.
** The only way to test क्रम that is to place a loopback packet onto the
** network and watch क्रम errors. Since we're messing with the पूर्णांकerrupt mask
** रेजिस्टर, disable the board पूर्णांकerrupts and करो not allow any more packets to
** be queued to the hardware. Re-enable everything only when the media is
** found.
** I may have to "age out" locally queued packets so that the higher layer
** समयouts करोn't effectively duplicate packets on the network.
*/
अटल पूर्णांक
dc21040_स्वतःconf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;
    s32 imr;

    चयन (lp->media) अणु
    हाल INIT:
	DISABLE_IRQs;
	lp->tx_enable = false;
	lp->समयout = -1;
	de4x5_save_skbs(dev);
	अगर ((lp->स्वतःsense == AUTO) || (lp->स्वतःsense == TP)) अणु
	    lp->media = TP;
	पूर्ण अन्यथा अगर ((lp->स्वतःsense == BNC) || (lp->स्वतःsense == AUI) || (lp->स्वतःsense == BNC_AUI)) अणु
	    lp->media = BNC_AUI;
	पूर्ण अन्यथा अगर (lp->स्वतःsense == EXT_SIA) अणु
	    lp->media = EXT_SIA;
	पूर्ण अन्यथा अणु
	    lp->media = NC;
	पूर्ण
	lp->local_state = 0;
	next_tick = dc21040_स्वतःconf(dev);
	अवरोध;

    हाल TP:
	next_tick = dc21040_state(dev, 0x8f01, 0xffff, 0x0000, 3000, BNC_AUI,
		                                         TP_SUSPECT, test_tp);
	अवरोध;

    हाल TP_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, TP, test_tp, dc21040_स्वतःconf);
	अवरोध;

    हाल BNC:
    हाल AUI:
    हाल BNC_AUI:
	next_tick = dc21040_state(dev, 0x8f09, 0x0705, 0x0006, 3000, EXT_SIA,
		                                  BNC_AUI_SUSPECT, ping_media);
	अवरोध;

    हाल BNC_AUI_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, BNC_AUI, ping_media, dc21040_स्वतःconf);
	अवरोध;

    हाल EXT_SIA:
	next_tick = dc21040_state(dev, 0x3041, 0x0000, 0x0006, 3000,
		                              NC, EXT_SIA_SUSPECT, ping_media);
	अवरोध;

    हाल EXT_SIA_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, EXT_SIA, ping_media, dc21040_स्वतःconf);
	अवरोध;

    हाल NC:
	/* शेष to TP क्रम all */
	reset_init_sia(dev, 0x8f01, 0xffff, 0x0000);
	अगर (lp->media != lp->c_media) अणु
	    de4x5_dbg_media(dev);
	    lp->c_media = lp->media;
	पूर्ण
	lp->media = INIT;
	lp->tx_enable = false;
	अवरोध;
    पूर्ण

    वापस next_tick;
पूर्ण

अटल पूर्णांक
dc21040_state(काष्ठा net_device *dev, पूर्णांक csr13, पूर्णांक csr14, पूर्णांक csr15, पूर्णांक समयout,
	      पूर्णांक next_state, पूर्णांक suspect_state,
	      पूर्णांक (*fn)(काष्ठा net_device *, पूर्णांक))
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;
    पूर्णांक linkBad;

    चयन (lp->local_state) अणु
    हाल 0:
	reset_init_sia(dev, csr13, csr14, csr15);
	lp->local_state++;
	next_tick = 500;
	अवरोध;

    हाल 1:
	अगर (!lp->tx_enable) अणु
	    linkBad = fn(dev, समयout);
	    अगर (linkBad < 0) अणु
		next_tick = linkBad & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		अगर (linkBad && (lp->स्वतःsense == AUTO)) अणु
		    lp->local_state = 0;
		    lp->media = next_state;
		पूर्ण अन्यथा अणु
		    de4x5_init_connection(dev);
		पूर्ण
	    पूर्ण
	पूर्ण अन्यथा अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
	    lp->media = suspect_state;
	    next_tick = 3000;
	पूर्ण
	अवरोध;
    पूर्ण

    वापस next_tick;
पूर्ण

अटल पूर्णांक
de4x5_suspect_state(काष्ठा net_device *dev, पूर्णांक समयout, पूर्णांक prev_state,
		      पूर्णांक (*fn)(काष्ठा net_device *, पूर्णांक),
		      पूर्णांक (*asfn)(काष्ठा net_device *))
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;
    पूर्णांक linkBad;

    चयन (lp->local_state) अणु
    हाल 1:
	अगर (lp->linkOK) अणु
	    lp->media = prev_state;
	पूर्ण अन्यथा अणु
	    lp->local_state++;
	    next_tick = asfn(dev);
	पूर्ण
	अवरोध;

    हाल 2:
	linkBad = fn(dev, समयout);
	अगर (linkBad < 0) अणु
	    next_tick = linkBad & ~TIMER_CB;
	पूर्ण अन्यथा अगर (!linkBad) अणु
	    lp->local_state--;
	    lp->media = prev_state;
	पूर्ण अन्यथा अणु
	    lp->media = INIT;
	    lp->tcount++;
	पूर्ण
    पूर्ण

    वापस next_tick;
पूर्ण

/*
** Autoconfigure the media when using the DC21041. AUI needs to be tested
** beक्रमe BNC, because the BNC port will indicate activity अगर it's not
** terminated correctly. The only way to test क्रम that is to place a loopback
** packet onto the network and watch क्रम errors. Since we're messing with
** the पूर्णांकerrupt mask रेजिस्टर, disable the board पूर्णांकerrupts and करो not allow
** any more packets to be queued to the hardware. Re-enable everything only
** when the media is found.
*/
अटल पूर्णांक
dc21041_स्वतःconf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 sts, irqs, irq_mask, imr, omr;
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;

    चयन (lp->media) अणु
    हाल INIT:
	DISABLE_IRQs;
	lp->tx_enable = false;
	lp->समयout = -1;
	de4x5_save_skbs(dev);          /* Save non transmitted skb's */
	अगर ((lp->स्वतःsense == AUTO) || (lp->स्वतःsense == TP_NW)) अणु
	    lp->media = TP;            /* On chip स्वतः negotiation is broken */
	पूर्ण अन्यथा अगर (lp->स्वतःsense == TP) अणु
	    lp->media = TP;
	पूर्ण अन्यथा अगर (lp->स्वतःsense == BNC) अणु
	    lp->media = BNC;
	पूर्ण अन्यथा अगर (lp->स्वतःsense == AUI) अणु
	    lp->media = AUI;
	पूर्ण अन्यथा अणु
	    lp->media = NC;
	पूर्ण
	lp->local_state = 0;
	next_tick = dc21041_स्वतःconf(dev);
	अवरोध;

    हाल TP_NW:
	अगर (lp->समयout < 0) अणु
	    omr = inl(DE4X5_OMR);/* Set up full duplex क्रम the स्वतःnegotiate */
	    outl(omr | OMR_FDX, DE4X5_OMR);
	पूर्ण
	irqs = STS_LNF | STS_LNP;
	irq_mask = IMR_LFM | IMR_LPM;
	sts = test_media(dev, irqs, irq_mask, 0xef01, 0xffff, 0x0008, 2400);
	अगर (sts < 0) अणु
	    next_tick = sts & ~TIMER_CB;
	पूर्ण अन्यथा अणु
	    अगर (sts & STS_LNP) अणु
		lp->media = ANS;
	    पूर्ण अन्यथा अणु
		lp->media = AUI;
	    पूर्ण
	    next_tick = dc21041_स्वतःconf(dev);
	पूर्ण
	अवरोध;

    हाल ANS:
	अगर (!lp->tx_enable) अणु
	    irqs = STS_LNP;
	    irq_mask = IMR_LPM;
	    sts = test_ans(dev, irqs, irq_mask, 3000);
	    अगर (sts < 0) अणु
		next_tick = sts & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		अगर (!(sts & STS_LNP) && (lp->स्वतःsense == AUTO)) अणु
		    lp->media = TP;
		    next_tick = dc21041_स्वतःconf(dev);
		पूर्ण अन्यथा अणु
		    lp->local_state = 1;
		    de4x5_init_connection(dev);
		पूर्ण
	    पूर्ण
	पूर्ण अन्यथा अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
	    lp->media = ANS_SUSPECT;
	    next_tick = 3000;
	पूर्ण
	अवरोध;

    हाल ANS_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, ANS, test_tp, dc21041_स्वतःconf);
	अवरोध;

    हाल TP:
	अगर (!lp->tx_enable) अणु
	    अगर (lp->समयout < 0) अणु
		omr = inl(DE4X5_OMR);          /* Set up half duplex क्रम TP */
		outl(omr & ~OMR_FDX, DE4X5_OMR);
	    पूर्ण
	    irqs = STS_LNF | STS_LNP;
	    irq_mask = IMR_LFM | IMR_LPM;
	    sts = test_media(dev,irqs, irq_mask, 0xef01, 0xff3f, 0x0008, 2400);
	    अगर (sts < 0) अणु
		next_tick = sts & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		अगर (!(sts & STS_LNP) && (lp->स्वतःsense == AUTO)) अणु
		    अगर (inl(DE4X5_SISR) & SISR_NRA) अणु
			lp->media = AUI;       /* Non selected port activity */
		    पूर्ण अन्यथा अणु
			lp->media = BNC;
		    पूर्ण
		    next_tick = dc21041_स्वतःconf(dev);
		पूर्ण अन्यथा अणु
		    lp->local_state = 1;
		    de4x5_init_connection(dev);
		पूर्ण
	    पूर्ण
	पूर्ण अन्यथा अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
	    lp->media = TP_SUSPECT;
	    next_tick = 3000;
	पूर्ण
	अवरोध;

    हाल TP_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, TP, test_tp, dc21041_स्वतःconf);
	अवरोध;

    हाल AUI:
	अगर (!lp->tx_enable) अणु
	    अगर (lp->समयout < 0) अणु
		omr = inl(DE4X5_OMR);          /* Set up half duplex क्रम AUI */
		outl(omr & ~OMR_FDX, DE4X5_OMR);
	    पूर्ण
	    irqs = 0;
	    irq_mask = 0;
	    sts = test_media(dev,irqs, irq_mask, 0xef09, 0xf73d, 0x000e, 1000);
	    अगर (sts < 0) अणु
		next_tick = sts & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		अगर (!(inl(DE4X5_SISR) & SISR_SRA) && (lp->स्वतःsense == AUTO)) अणु
		    lp->media = BNC;
		    next_tick = dc21041_स्वतःconf(dev);
		पूर्ण अन्यथा अणु
		    lp->local_state = 1;
		    de4x5_init_connection(dev);
		पूर्ण
	    पूर्ण
	पूर्ण अन्यथा अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
	    lp->media = AUI_SUSPECT;
	    next_tick = 3000;
	पूर्ण
	अवरोध;

    हाल AUI_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, AUI, ping_media, dc21041_स्वतःconf);
	अवरोध;

    हाल BNC:
	चयन (lp->local_state) अणु
	हाल 0:
	    अगर (lp->समयout < 0) अणु
		omr = inl(DE4X5_OMR);          /* Set up half duplex क्रम BNC */
		outl(omr & ~OMR_FDX, DE4X5_OMR);
	    पूर्ण
	    irqs = 0;
	    irq_mask = 0;
	    sts = test_media(dev,irqs, irq_mask, 0xef09, 0xf73d, 0x0006, 1000);
	    अगर (sts < 0) अणु
		next_tick = sts & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		lp->local_state++;             /* Ensure media connected */
		next_tick = dc21041_स्वतःconf(dev);
	    पूर्ण
	    अवरोध;

	हाल 1:
	    अगर (!lp->tx_enable) अणु
		अगर ((sts = ping_media(dev, 3000)) < 0) अणु
		    next_tick = sts & ~TIMER_CB;
		पूर्ण अन्यथा अणु
		    अगर (sts) अणु
			lp->local_state = 0;
			lp->media = NC;
		    पूर्ण अन्यथा अणु
			de4x5_init_connection(dev);
		    पूर्ण
		पूर्ण
	    पूर्ण अन्यथा अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
		lp->media = BNC_SUSPECT;
		next_tick = 3000;
	    पूर्ण
	    अवरोध;
	पूर्ण
	अवरोध;

    हाल BNC_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, BNC, ping_media, dc21041_स्वतःconf);
	अवरोध;

    हाल NC:
	omr = inl(DE4X5_OMR);    /* Set up full duplex क्रम the स्वतःnegotiate */
	outl(omr | OMR_FDX, DE4X5_OMR);
	reset_init_sia(dev, 0xef01, 0xffff, 0x0008);/* Initialise the SIA */
	अगर (lp->media != lp->c_media) अणु
	    de4x5_dbg_media(dev);
	    lp->c_media = lp->media;
	पूर्ण
	lp->media = INIT;
	lp->tx_enable = false;
	अवरोध;
    पूर्ण

    वापस next_tick;
पूर्ण

/*
** Some स्वतःnegotiation chips are broken in that they करो not वापस the
** acknowledge bit (anlpa & MII_ANLPA_ACK) in the link partner advertisement
** रेजिस्टर, except at the first घातer up negotiation.
*/
अटल पूर्णांक
dc21140m_स्वतःconf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक ana, anlpa, cap, cr, slnk, sr;
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;
    u_दीर्घ imr, omr, iobase = dev->base_addr;

    चयन(lp->media) अणु
    हाल INIT:
        अगर (lp->समयout < 0) अणु
	    DISABLE_IRQs;
	    lp->tx_enable = false;
	    lp->linkOK = 0;
	    de4x5_save_skbs(dev);          /* Save non transmitted skb's */
	पूर्ण
	अगर ((next_tick = de4x5_reset_phy(dev)) < 0) अणु
	    next_tick &= ~TIMER_CB;
	पूर्ण अन्यथा अणु
	    अगर (lp->useSROM) अणु
		अगर (srom_map_media(dev) < 0) अणु
		    lp->tcount++;
		    वापस next_tick;
		पूर्ण
		srom_exec(dev, lp->phy[lp->active].gep);
		अगर (lp->infoblock_media == ANS) अणु
		    ana = lp->phy[lp->active].ana | MII_ANA_CSMA;
		    mii_wr(ana, MII_ANA, lp->phy[lp->active].addr, DE4X5_MII);
		पूर्ण
	    पूर्ण अन्यथा अणु
		lp->पंचांगp = MII_SR_ASSC;     /* Fake out the MII speed set */
		SET_10Mb;
		अगर (lp->स्वतःsense == _100Mb) अणु
		    lp->media = _100Mb;
		पूर्ण अन्यथा अगर (lp->स्वतःsense == _10Mb) अणु
		    lp->media = _10Mb;
		पूर्ण अन्यथा अगर ((lp->स्वतःsense == AUTO) &&
			            ((sr=is_anc_capable(dev)) & MII_SR_ANC)) अणु
		    ana = (((sr >> 6) & MII_ANA_TAF) | MII_ANA_CSMA);
		    ana &= (lp->fdx ? ~0 : ~MII_ANA_FDAM);
		    mii_wr(ana, MII_ANA, lp->phy[lp->active].addr, DE4X5_MII);
		    lp->media = ANS;
		पूर्ण अन्यथा अगर (lp->स्वतःsense == AUTO) अणु
		    lp->media = SPD_DET;
		पूर्ण अन्यथा अगर (is_spd_100(dev) && is_100_up(dev)) अणु
		    lp->media = _100Mb;
		पूर्ण अन्यथा अणु
		    lp->media = NC;
		पूर्ण
	    पूर्ण
	    lp->local_state = 0;
	    next_tick = dc21140m_स्वतःconf(dev);
	पूर्ण
	अवरोध;

    हाल ANS:
	चयन (lp->local_state) अणु
	हाल 0:
	    अगर (lp->समयout < 0) अणु
		mii_wr(MII_CR_ASSE | MII_CR_RAN, MII_CR, lp->phy[lp->active].addr, DE4X5_MII);
	    पूर्ण
	    cr = test_mii_reg(dev, MII_CR, MII_CR_RAN, false, 500);
	    अगर (cr < 0) अणु
		next_tick = cr & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		अगर (cr) अणु
		    lp->local_state = 0;
		    lp->media = SPD_DET;
		पूर्ण अन्यथा अणु
		    lp->local_state++;
		पूर्ण
		next_tick = dc21140m_स्वतःconf(dev);
	    पूर्ण
	    अवरोध;

	हाल 1:
	    अगर ((sr=test_mii_reg(dev, MII_SR, MII_SR_ASSC, true, 2000)) < 0) अणु
		next_tick = sr & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		lp->media = SPD_DET;
		lp->local_state = 0;
		अगर (sr) अणु                         /* Success! */
		    lp->पंचांगp = MII_SR_ASSC;
		    anlpa = mii_rd(MII_ANLPA, lp->phy[lp->active].addr, DE4X5_MII);
		    ana = mii_rd(MII_ANA, lp->phy[lp->active].addr, DE4X5_MII);
		    अगर (!(anlpa & MII_ANLPA_RF) &&
			 (cap = anlpa & MII_ANLPA_TAF & ana)) अणु
			अगर (cap & MII_ANA_100M) अणु
			    lp->fdx = (ana & anlpa & MII_ANA_FDAM & MII_ANA_100M) != 0;
			    lp->media = _100Mb;
			पूर्ण अन्यथा अगर (cap & MII_ANA_10M) अणु
			    lp->fdx = (ana & anlpa & MII_ANA_FDAM & MII_ANA_10M) != 0;

			    lp->media = _10Mb;
			पूर्ण
		    पूर्ण
		पूर्ण                       /* Auto Negotiation failed to finish */
		next_tick = dc21140m_स्वतःconf(dev);
	    पूर्ण                           /* Auto Negotiation failed to start */
	    अवरोध;
	पूर्ण
	अवरोध;

    हाल SPD_DET:                              /* Choose 10Mb/s or 100Mb/s */
        अगर (lp->समयout < 0) अणु
	    lp->पंचांगp = (lp->phy[lp->active].id ? MII_SR_LKS :
		                                  (~gep_rd(dev) & GEP_LNP));
	    SET_100Mb_PDET;
	पूर्ण
        अगर ((slnk = test_क्रम_100Mb(dev, 6500)) < 0) अणु
	    next_tick = slnk & ~TIMER_CB;
	पूर्ण अन्यथा अणु
	    अगर (is_spd_100(dev) && is_100_up(dev)) अणु
		lp->media = _100Mb;
	    पूर्ण अन्यथा अगर ((!is_spd_100(dev) && (is_10_up(dev) & lp->पंचांगp))) अणु
		lp->media = _10Mb;
	    पूर्ण अन्यथा अणु
		lp->media = NC;
	    पूर्ण
	    next_tick = dc21140m_स्वतःconf(dev);
	पूर्ण
	अवरोध;

    हाल _100Mb:                               /* Set 100Mb/s */
        next_tick = 3000;
	अगर (!lp->tx_enable) अणु
	    SET_100Mb;
	    de4x5_init_connection(dev);
	पूर्ण अन्यथा अणु
	    अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
		अगर (!is_100_up(dev) || (!lp->useSROM && !is_spd_100(dev))) अणु
		    lp->media = INIT;
		    lp->tcount++;
		    next_tick = DE4X5_AUTOSENSE_MS;
		पूर्ण
	    पूर्ण
	पूर्ण
	अवरोध;

    हाल BNC:
    हाल AUI:
    हाल _10Mb:                                /* Set 10Mb/s */
        next_tick = 3000;
	अगर (!lp->tx_enable) अणु
	    SET_10Mb;
	    de4x5_init_connection(dev);
	पूर्ण अन्यथा अणु
	    अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
		अगर (!is_10_up(dev) || (!lp->useSROM && is_spd_100(dev))) अणु
		    lp->media = INIT;
		    lp->tcount++;
		    next_tick = DE4X5_AUTOSENSE_MS;
		पूर्ण
	    पूर्ण
	पूर्ण
	अवरोध;

    हाल NC:
        अगर (lp->media != lp->c_media) अणु
	    de4x5_dbg_media(dev);
	    lp->c_media = lp->media;
	पूर्ण
	lp->media = INIT;
	lp->tx_enable = false;
	अवरोध;
    पूर्ण

    वापस next_tick;
पूर्ण

/*
** This routine may be merged पूर्णांकo dc21140m_स्वतःconf() someसमय as I'm
** changing how I figure out the media - but trying to keep it backwards
** compatible with the de500-xa and de500-aa.
** Whether it's BNC, AUI, SYM or MII is sorted out in the infoblock
** functions and set during de4x5_mac_port() and/or de4x5_reset_phy().
** This routine just has to figure out whether 10Mb/s or 100Mb/s is
** active.
** When स्वतःnegotiation is working, the ANS part searches the SROM क्रम
** the highest common speed (TP) link that both can run and अगर that can
** be full duplex. That infoblock is executed and then the link speed set.
**
** Only _10Mb and _100Mb are tested here.
*/
अटल पूर्णांक
dc2114x_स्वतःconf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 cr, anlpa, ana, cap, irqs, irq_mask, imr, omr, slnk, sr, sts;
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;

    चयन (lp->media) अणु
    हाल INIT:
        अगर (lp->समयout < 0) अणु
	    DISABLE_IRQs;
	    lp->tx_enable = false;
	    lp->linkOK = 0;
            lp->समयout = -1;
	    de4x5_save_skbs(dev);            /* Save non transmitted skb's */
	    अगर (lp->params.स्वतःsense & ~AUTO) अणु
		srom_map_media(dev);         /* Fixed media requested      */
		अगर (lp->media != lp->params.स्वतःsense) अणु
		    lp->tcount++;
		    lp->media = INIT;
		    वापस next_tick;
		पूर्ण
		lp->media = INIT;
	    पूर्ण
	पूर्ण
	अगर ((next_tick = de4x5_reset_phy(dev)) < 0) अणु
	    next_tick &= ~TIMER_CB;
	पूर्ण अन्यथा अणु
	    अगर (lp->स्वतःsense == _100Mb) अणु
		lp->media = _100Mb;
	    पूर्ण अन्यथा अगर (lp->स्वतःsense == _10Mb) अणु
		lp->media = _10Mb;
	    पूर्ण अन्यथा अगर (lp->स्वतःsense == TP) अणु
		lp->media = TP;
	    पूर्ण अन्यथा अगर (lp->स्वतःsense == BNC) अणु
		lp->media = BNC;
	    पूर्ण अन्यथा अगर (lp->स्वतःsense == AUI) अणु
		lp->media = AUI;
	    पूर्ण अन्यथा अणु
		lp->media = SPD_DET;
		अगर ((lp->infoblock_media == ANS) &&
		                    ((sr=is_anc_capable(dev)) & MII_SR_ANC)) अणु
		    ana = (((sr >> 6) & MII_ANA_TAF) | MII_ANA_CSMA);
		    ana &= (lp->fdx ? ~0 : ~MII_ANA_FDAM);
		    mii_wr(ana, MII_ANA, lp->phy[lp->active].addr, DE4X5_MII);
		    lp->media = ANS;
		पूर्ण
	    पूर्ण
	    lp->local_state = 0;
	    next_tick = dc2114x_स्वतःconf(dev);
        पूर्ण
	अवरोध;

    हाल ANS:
	चयन (lp->local_state) अणु
	हाल 0:
	    अगर (lp->समयout < 0) अणु
		mii_wr(MII_CR_ASSE | MII_CR_RAN, MII_CR, lp->phy[lp->active].addr, DE4X5_MII);
	    पूर्ण
	    cr = test_mii_reg(dev, MII_CR, MII_CR_RAN, false, 500);
	    अगर (cr < 0) अणु
		next_tick = cr & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		अगर (cr) अणु
		    lp->local_state = 0;
		    lp->media = SPD_DET;
		पूर्ण अन्यथा अणु
		    lp->local_state++;
		पूर्ण
		next_tick = dc2114x_स्वतःconf(dev);
	    पूर्ण
	    अवरोध;

	हाल 1:
	    sr = test_mii_reg(dev, MII_SR, MII_SR_ASSC, true, 2000);
	    अगर (sr < 0) अणु
		next_tick = sr & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		lp->media = SPD_DET;
		lp->local_state = 0;
		अगर (sr) अणु                         /* Success! */
		    lp->पंचांगp = MII_SR_ASSC;
		    anlpa = mii_rd(MII_ANLPA, lp->phy[lp->active].addr, DE4X5_MII);
		    ana = mii_rd(MII_ANA, lp->phy[lp->active].addr, DE4X5_MII);
		    अगर (!(anlpa & MII_ANLPA_RF) &&
			 (cap = anlpa & MII_ANLPA_TAF & ana)) अणु
			अगर (cap & MII_ANA_100M) अणु
			    lp->fdx = (ana & anlpa & MII_ANA_FDAM & MII_ANA_100M) != 0;
			    lp->media = _100Mb;
			पूर्ण अन्यथा अगर (cap & MII_ANA_10M) अणु
			    lp->fdx = (ana & anlpa & MII_ANA_FDAM & MII_ANA_10M) != 0;
			    lp->media = _10Mb;
			पूर्ण
		    पूर्ण
		पूर्ण                       /* Auto Negotiation failed to finish */
		next_tick = dc2114x_स्वतःconf(dev);
	    पूर्ण                           /* Auto Negotiation failed to start  */
	    अवरोध;
	पूर्ण
	अवरोध;

    हाल AUI:
	अगर (!lp->tx_enable) अणु
	    अगर (lp->समयout < 0) अणु
		omr = inl(DE4X5_OMR);   /* Set up half duplex क्रम AUI        */
		outl(omr & ~OMR_FDX, DE4X5_OMR);
	    पूर्ण
	    irqs = 0;
	    irq_mask = 0;
	    sts = test_media(dev,irqs, irq_mask, 0, 0, 0, 1000);
	    अगर (sts < 0) अणु
		next_tick = sts & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		अगर (!(inl(DE4X5_SISR) & SISR_SRA) && (lp->स्वतःsense == AUTO)) अणु
		    lp->media = BNC;
		    next_tick = dc2114x_स्वतःconf(dev);
		पूर्ण अन्यथा अणु
		    lp->local_state = 1;
		    de4x5_init_connection(dev);
		पूर्ण
	    पूर्ण
	पूर्ण अन्यथा अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
	    lp->media = AUI_SUSPECT;
	    next_tick = 3000;
	पूर्ण
	अवरोध;

    हाल AUI_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, AUI, ping_media, dc2114x_स्वतःconf);
	अवरोध;

    हाल BNC:
	चयन (lp->local_state) अणु
	हाल 0:
	    अगर (lp->समयout < 0) अणु
		omr = inl(DE4X5_OMR);          /* Set up half duplex क्रम BNC */
		outl(omr & ~OMR_FDX, DE4X5_OMR);
	    पूर्ण
	    irqs = 0;
	    irq_mask = 0;
	    sts = test_media(dev,irqs, irq_mask, 0, 0, 0, 1000);
	    अगर (sts < 0) अणु
		next_tick = sts & ~TIMER_CB;
	    पूर्ण अन्यथा अणु
		lp->local_state++;             /* Ensure media connected */
		next_tick = dc2114x_स्वतःconf(dev);
	    पूर्ण
	    अवरोध;

	हाल 1:
	    अगर (!lp->tx_enable) अणु
		अगर ((sts = ping_media(dev, 3000)) < 0) अणु
		    next_tick = sts & ~TIMER_CB;
		पूर्ण अन्यथा अणु
		    अगर (sts) अणु
			lp->local_state = 0;
			lp->tcount++;
			lp->media = INIT;
		    पूर्ण अन्यथा अणु
			de4x5_init_connection(dev);
		    पूर्ण
		पूर्ण
	    पूर्ण अन्यथा अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
		lp->media = BNC_SUSPECT;
		next_tick = 3000;
	    पूर्ण
	    अवरोध;
	पूर्ण
	अवरोध;

    हाल BNC_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, BNC, ping_media, dc2114x_स्वतःconf);
	अवरोध;

    हाल SPD_DET:                              /* Choose 10Mb/s or 100Mb/s */
	  अगर (srom_map_media(dev) < 0) अणु
	      lp->tcount++;
	      lp->media = INIT;
	      वापस next_tick;
	  पूर्ण
	  अगर (lp->media == _100Mb) अणु
	      अगर ((slnk = test_क्रम_100Mb(dev, 6500)) < 0) अणु
		  lp->media = SPD_DET;
		  वापस slnk & ~TIMER_CB;
	      पूर्ण
	  पूर्ण अन्यथा अणु
	      अगर (रुको_क्रम_link(dev) < 0) अणु
		  lp->media = SPD_DET;
		  वापस PDET_LINK_WAIT;
	      पूर्ण
	  पूर्ण
	  अगर (lp->media == ANS) अणु           /* Do MII parallel detection */
	      अगर (is_spd_100(dev)) अणु
		  lp->media = _100Mb;
	      पूर्ण अन्यथा अणु
		  lp->media = _10Mb;
	      पूर्ण
	      next_tick = dc2114x_स्वतःconf(dev);
	  पूर्ण अन्यथा अगर (((lp->media == _100Mb) && is_100_up(dev)) ||
		     (((lp->media == _10Mb) || (lp->media == TP) ||
		       (lp->media == BNC)   || (lp->media == AUI)) &&
		      is_10_up(dev))) अणु
	      next_tick = dc2114x_स्वतःconf(dev);
	  पूर्ण अन्यथा अणु
	      lp->tcount++;
	      lp->media = INIT;
	  पूर्ण
	  अवरोध;

    हाल _10Mb:
        next_tick = 3000;
	अगर (!lp->tx_enable) अणु
	    SET_10Mb;
	    de4x5_init_connection(dev);
	पूर्ण अन्यथा अणु
	    अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
		अगर (!is_10_up(dev) || (!lp->useSROM && is_spd_100(dev))) अणु
		    lp->media = INIT;
		    lp->tcount++;
		    next_tick = DE4X5_AUTOSENSE_MS;
		पूर्ण
	    पूर्ण
	पूर्ण
	अवरोध;

    हाल _100Mb:
        next_tick = 3000;
	अगर (!lp->tx_enable) अणु
	    SET_100Mb;
	    de4x5_init_connection(dev);
	पूर्ण अन्यथा अणु
	    अगर (!lp->linkOK && (lp->स्वतःsense == AUTO)) अणु
		अगर (!is_100_up(dev) || (!lp->useSROM && !is_spd_100(dev))) अणु
		    lp->media = INIT;
		    lp->tcount++;
		    next_tick = DE4X5_AUTOSENSE_MS;
		पूर्ण
	    पूर्ण
	पूर्ण
	अवरोध;

    शेष:
	lp->tcount++;
prपूर्णांकk("Huh?: media:%02x\n", lp->media);
	lp->media = INIT;
	अवरोध;
    पूर्ण

    वापस next_tick;
पूर्ण

अटल पूर्णांक
srom_स्वतःconf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    वापस lp->infoleaf_fn(dev);
पूर्ण

/*
** This mapping keeps the original media codes and FDX flag unchanged.
** While it isn't strictly necessary, it helps me क्रम the moment...
** The early वापस aव्योमs a media state / SROM media space clash.
*/
अटल पूर्णांक
srom_map_media(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    lp->fdx = false;
    अगर (lp->infoblock_media == lp->media)
      वापस 0;

    चयन(lp->infoblock_media) अणु
      हाल SROM_10BASETF:
	अगर (!lp->params.fdx) वापस -1;
	lp->fdx = true;
	fallthrough;

      हाल SROM_10BASET:
	अगर (lp->params.fdx && !lp->fdx) वापस -1;
	अगर ((lp->chipset == DC21140) || ((lp->chipset & ~0x00ff) == DC2114x)) अणु
	    lp->media = _10Mb;
	पूर्ण अन्यथा अणु
	    lp->media = TP;
	पूर्ण
	अवरोध;

      हाल SROM_10BASE2:
	lp->media = BNC;
	अवरोध;

      हाल SROM_10BASE5:
	lp->media = AUI;
	अवरोध;

      हाल SROM_100BASETF:
        अगर (!lp->params.fdx) वापस -1;
	lp->fdx = true;
	fallthrough;

      हाल SROM_100BASET:
	अगर (lp->params.fdx && !lp->fdx) वापस -1;
	lp->media = _100Mb;
	अवरोध;

      हाल SROM_100BASET4:
	lp->media = _100Mb;
	अवरोध;

      हाल SROM_100BASEFF:
	अगर (!lp->params.fdx) वापस -1;
	lp->fdx = true;
	fallthrough;

      हाल SROM_100BASEF:
	अगर (lp->params.fdx && !lp->fdx) वापस -1;
	lp->media = _100Mb;
	अवरोध;

      हाल ANS:
	lp->media = ANS;
	lp->fdx = lp->params.fdx;
	अवरोध;

      शेष:
	prपूर्णांकk("%s: Bad media code [%d] detected in SROM!\n", dev->name,
	                                                  lp->infoblock_media);
	वापस -1;
    पूर्ण

    वापस 0;
पूर्ण

अटल व्योम
de4x5_init_connection(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    u_दीर्घ flags = 0;

    अगर (lp->media != lp->c_media) अणु
        de4x5_dbg_media(dev);
	lp->c_media = lp->media;          /* Stop scrolling media messages */
    पूर्ण

    spin_lock_irqsave(&lp->lock, flags);
    de4x5_rst_desc_ring(dev);
    de4x5_setup_पूर्णांकr(dev);
    lp->tx_enable = true;
    spin_unlock_irqrestore(&lp->lock, flags);
    outl(POLL_DEMAND, DE4X5_TPD);

    netअगर_wake_queue(dev);
पूर्ण

/*
** General PHY reset function. Some MII devices करोn't reset correctly
** since their MII address pins can भग्न at voltages that are dependent
** on the संकेत pin use. Do a द्विगुन reset to ensure a reset.
*/
अटल पूर्णांक
de4x5_reset_phy(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक next_tick = 0;

    अगर ((lp->useSROM) || (lp->phy[lp->active].id)) अणु
	अगर (lp->समयout < 0) अणु
	    अगर (lp->useSROM) अणु
		अगर (lp->phy[lp->active].rst) अणु
		    srom_exec(dev, lp->phy[lp->active].rst);
		    srom_exec(dev, lp->phy[lp->active].rst);
		पूर्ण अन्यथा अगर (lp->rst) अणु          /* Type 5 infoblock reset */
		    srom_exec(dev, lp->rst);
		    srom_exec(dev, lp->rst);
		पूर्ण
	    पूर्ण अन्यथा अणु
		PHY_HARD_RESET;
	    पूर्ण
	    अगर (lp->useMII) अणु
	        mii_wr(MII_CR_RST, MII_CR, lp->phy[lp->active].addr, DE4X5_MII);
            पूर्ण
        पूर्ण
	अगर (lp->useMII) अणु
	    next_tick = test_mii_reg(dev, MII_CR, MII_CR_RST, false, 500);
	पूर्ण
    पूर्ण अन्यथा अगर (lp->chipset == DC21140) अणु
	PHY_HARD_RESET;
    पूर्ण

    वापस next_tick;
पूर्ण

अटल पूर्णांक
test_media(काष्ठा net_device *dev, s32 irqs, s32 irq_mask, s32 csr13, s32 csr14, s32 csr15, s32 msec)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 sts, csr12;

    अगर (lp->समयout < 0) अणु
	lp->समयout = msec/100;
	अगर (!lp->useSROM) अणु      /* Alपढ़ोy करोne अगर by SROM, अन्यथा dc2104[01] */
	    reset_init_sia(dev, csr13, csr14, csr15);
	पूर्ण

	/* set up the पूर्णांकerrupt mask */
	outl(irq_mask, DE4X5_IMR);

	/* clear all pending पूर्णांकerrupts */
	sts = inl(DE4X5_STS);
	outl(sts, DE4X5_STS);

	/* clear csr12 NRA and SRA bits */
	अगर ((lp->chipset == DC21041) || lp->useSROM) अणु
	    csr12 = inl(DE4X5_SISR);
	    outl(csr12, DE4X5_SISR);
	पूर्ण
    पूर्ण

    sts = inl(DE4X5_STS) & ~TIMER_CB;

    अगर (!(sts & irqs) && --lp->समयout) अणु
	sts = 100 | TIMER_CB;
    पूर्ण अन्यथा अणु
	lp->समयout = -1;
    पूर्ण

    वापस sts;
पूर्ण

अटल पूर्णांक
test_tp(काष्ठा net_device *dev, s32 msec)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक sisr;

    अगर (lp->समयout < 0) अणु
	lp->समयout = msec/100;
    पूर्ण

    sisr = (inl(DE4X5_SISR) & ~TIMER_CB) & (SISR_LKF | SISR_NCR);

    अगर (sisr && --lp->समयout) अणु
	sisr = 100 | TIMER_CB;
    पूर्ण अन्यथा अणु
	lp->समयout = -1;
    पूर्ण

    वापस sisr;
पूर्ण

/*
** Samples the 100Mb Link State Signal. The sample पूर्णांकerval is important
** because too fast a rate can give erroneous results and confuse the
** speed sense algorithm.
*/
#घोषणा SAMPLE_INTERVAL 500  /* ms */
#घोषणा SAMPLE_DELAY    2000 /* ms */
अटल पूर्णांक
test_क्रम_100Mb(काष्ठा net_device *dev, पूर्णांक msec)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक gep = 0, ret = ((lp->chipset & ~0x00ff)==DC2114x? -1 :GEP_SLNK);

    अगर (lp->समयout < 0) अणु
	अगर ((msec/SAMPLE_INTERVAL) <= 0) वापस 0;
	अगर (msec > SAMPLE_DELAY) अणु
	    lp->समयout = (msec - SAMPLE_DELAY)/SAMPLE_INTERVAL;
	    gep = SAMPLE_DELAY | TIMER_CB;
	    वापस gep;
	पूर्ण अन्यथा अणु
	    lp->समयout = msec/SAMPLE_INTERVAL;
	पूर्ण
    पूर्ण

    अगर (lp->phy[lp->active].id || lp->useSROM) अणु
	gep = is_100_up(dev) | is_spd_100(dev);
    पूर्ण अन्यथा अणु
	gep = (~gep_rd(dev) & (GEP_SLNK | GEP_LNP));
    पूर्ण
    अगर (!(gep & ret) && --lp->समयout) अणु
	gep = SAMPLE_INTERVAL | TIMER_CB;
    पूर्ण अन्यथा अणु
	lp->समयout = -1;
    पूर्ण

    वापस gep;
पूर्ण

अटल पूर्णांक
रुको_क्रम_link(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    अगर (lp->समयout < 0) अणु
	lp->समयout = 1;
    पूर्ण

    अगर (lp->समयout--) अणु
	वापस TIMER_CB;
    पूर्ण अन्यथा अणु
	lp->समयout = -1;
    पूर्ण

    वापस 0;
पूर्ण

/*
**
**
*/
अटल पूर्णांक
test_mii_reg(काष्ठा net_device *dev, पूर्णांक reg, पूर्णांक mask, bool pol, दीर्घ msec)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक test;
    u_दीर्घ iobase = dev->base_addr;

    अगर (lp->समयout < 0) अणु
	lp->समयout = msec/100;
    पूर्ण

    reg = mii_rd((u_अक्षर)reg, lp->phy[lp->active].addr, DE4X5_MII) & mask;
    test = (reg ^ (pol ? ~0 : 0)) & mask;

    अगर (test && --lp->समयout) अणु
	reg = 100 | TIMER_CB;
    पूर्ण अन्यथा अणु
	lp->समयout = -1;
    पूर्ण

    वापस reg;
पूर्ण

अटल पूर्णांक
is_spd_100(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक spd;

    अगर (lp->useMII) अणु
	spd = mii_rd(lp->phy[lp->active].spd.reg, lp->phy[lp->active].addr, DE4X5_MII);
	spd = ~(spd ^ lp->phy[lp->active].spd.value);
	spd &= lp->phy[lp->active].spd.mask;
    पूर्ण अन्यथा अगर (!lp->useSROM) अणु                      /* de500-xa */
	spd = ((~gep_rd(dev)) & GEP_SLNK);
    पूर्ण अन्यथा अणु
	अगर ((lp->ibn == 2) || !lp->asBitValid)
	    वापस (lp->chipset == DC21143) ? (~inl(DE4X5_SISR)&SISR_LS100) : 0;

	spd = (lp->asBitValid & (lp->asPolarity ^ (gep_rd(dev) & lp->asBit))) |
	          (lp->linkOK & ~lp->asBitValid);
    पूर्ण

    वापस spd;
पूर्ण

अटल पूर्णांक
is_100_up(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    अगर (lp->useMII) अणु
	/* Double पढ़ो क्रम sticky bits & temporary drops */
	mii_rd(MII_SR, lp->phy[lp->active].addr, DE4X5_MII);
	वापस mii_rd(MII_SR, lp->phy[lp->active].addr, DE4X5_MII) & MII_SR_LKS;
    पूर्ण अन्यथा अगर (!lp->useSROM) अणु                       /* de500-xa */
	वापस (~gep_rd(dev)) & GEP_SLNK;
    पूर्ण अन्यथा अणु
	अगर ((lp->ibn == 2) || !lp->asBitValid)
	    वापस (lp->chipset == DC21143) ? (~inl(DE4X5_SISR)&SISR_LS100) : 0;

        वापस (lp->asBitValid&(lp->asPolarity^(gep_rd(dev)&lp->asBit))) |
		(lp->linkOK & ~lp->asBitValid);
    पूर्ण
पूर्ण

अटल पूर्णांक
is_10_up(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    अगर (lp->useMII) अणु
	/* Double पढ़ो क्रम sticky bits & temporary drops */
	mii_rd(MII_SR, lp->phy[lp->active].addr, DE4X5_MII);
	वापस mii_rd(MII_SR, lp->phy[lp->active].addr, DE4X5_MII) & MII_SR_LKS;
    पूर्ण अन्यथा अगर (!lp->useSROM) अणु                       /* de500-xa */
	वापस (~gep_rd(dev)) & GEP_LNP;
    पूर्ण अन्यथा अणु
	अगर ((lp->ibn == 2) || !lp->asBitValid)
	    वापस ((lp->chipset & ~0x00ff) == DC2114x) ?
		    (~inl(DE4X5_SISR)&SISR_LS10):
		    0;

	वापस	(lp->asBitValid&(lp->asPolarity^(gep_rd(dev)&lp->asBit))) |
		(lp->linkOK & ~lp->asBitValid);
    पूर्ण
पूर्ण

अटल पूर्णांक
is_anc_capable(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    अगर (lp->phy[lp->active].id && (!lp->useSROM || lp->useMII)) अणु
	वापस mii_rd(MII_SR, lp->phy[lp->active].addr, DE4X5_MII);
    पूर्ण अन्यथा अगर ((lp->chipset & ~0x00ff) == DC2114x) अणु
	वापस (inl(DE4X5_SISR) & SISR_LPN) >> 12;
    पूर्ण अन्यथा अणु
	वापस 0;
    पूर्ण
पूर्ण

/*
** Send a packet onto the media and watch क्रम send errors that indicate the
** media is bad or unconnected.
*/
अटल पूर्णांक
ping_media(काष्ठा net_device *dev, पूर्णांक msec)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक sisr;

    अगर (lp->समयout < 0) अणु
	lp->समयout = msec/100;

	lp->पंचांगp = lp->tx_new;                /* Remember the ring position */
	load_packet(dev, lp->frame, TD_LS | TD_FS | माप(lp->frame), (काष्ठा sk_buff *)1);
	lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;
	outl(POLL_DEMAND, DE4X5_TPD);
    पूर्ण

    sisr = inl(DE4X5_SISR);

    अगर ((!(sisr & SISR_NCR)) &&
	((s32)le32_to_cpu(lp->tx_ring[lp->पंचांगp].status) < 0) &&
	 (--lp->समयout)) अणु
	sisr = 100 | TIMER_CB;
    पूर्ण अन्यथा अणु
	अगर ((!(sisr & SISR_NCR)) &&
	    !(le32_to_cpu(lp->tx_ring[lp->पंचांगp].status) & (T_OWN | TD_ES)) &&
	    lp->समयout) अणु
	    sisr = 0;
	पूर्ण अन्यथा अणु
	    sisr = 1;
	पूर्ण
	lp->समयout = -1;
    पूर्ण

    वापस sisr;
पूर्ण

/*
** This function करोes 2 things: on Intels it kदो_स्मृति's another buffer to
** replace the one about to be passed up. On Alpha's it kदो_स्मृतिs a buffer
** पूर्णांकo which the packet is copied.
*/
अटल काष्ठा sk_buff *
de4x5_alloc_rx_buff(काष्ठा net_device *dev, पूर्णांक index, पूर्णांक len)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    काष्ठा sk_buff *p;

#अगर !defined(__alpha__) && !defined(__घातerpc__) && !defined(CONFIG_SPARC) && !defined(DE4X5_DO_MEMCPY)
    काष्ठा sk_buff *ret;
    u_दीर्घ i=0, पंचांगp;

    p = netdev_alloc_skb(dev, IEEE802_3_SZ + DE4X5_ALIGN + 2);
    अगर (!p) वापस शून्य;

    पंचांगp = virt_to_bus(p->data);
    i = ((पंचांगp + DE4X5_ALIGN) & ~DE4X5_ALIGN) - पंचांगp;
    skb_reserve(p, i);
    lp->rx_ring[index].buf = cpu_to_le32(पंचांगp + i);

    ret = lp->rx_skb[index];
    lp->rx_skb[index] = p;

    अगर ((u_दीर्घ) ret > 1) अणु
	skb_put(ret, len);
    पूर्ण

    वापस ret;

#अन्यथा
    अगर (lp->state != OPEN) वापस (काष्ठा sk_buff *)1; /* Fake out the खोलो */

    p = netdev_alloc_skb(dev, len + 2);
    अगर (!p) वापस शून्य;

    skb_reserve(p, 2);	                               /* Align */
    अगर (index < lp->rx_old) अणु                          /* Wrapped buffer */
	लघु tlen = (lp->rxRingSize - lp->rx_old) * RX_BUFF_SZ;
	skb_put_data(p, lp->rx_bufs + lp->rx_old * RX_BUFF_SZ, tlen);
	skb_put_data(p, lp->rx_bufs, len - tlen);
    पूर्ण अन्यथा अणु                                           /* Linear buffer */
	skb_put_data(p, lp->rx_bufs + lp->rx_old * RX_BUFF_SZ, len);
    पूर्ण

    वापस p;
#पूर्ण_अगर
पूर्ण

अटल व्योम
de4x5_मुक्त_rx_buffs(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक i;

    क्रम (i=0; i<lp->rxRingSize; i++) अणु
	अगर ((u_दीर्घ) lp->rx_skb[i] > 1) अणु
	    dev_kमुक्त_skb(lp->rx_skb[i]);
	पूर्ण
	lp->rx_ring[i].status = 0;
	lp->rx_skb[i] = (काष्ठा sk_buff *)1;    /* Dummy entry */
    पूर्ण
पूर्ण

अटल व्योम
de4x5_मुक्त_tx_buffs(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक i;

    क्रम (i=0; i<lp->txRingSize; i++) अणु
	अगर (lp->tx_skb[i])
	    de4x5_मुक्त_tx_buff(lp, i);
	lp->tx_ring[i].status = 0;
    पूर्ण

    /* Unload the locally queued packets */
    __skb_queue_purge(&lp->cache.queue);
पूर्ण

/*
** When a user pulls a connection, the DECchip can end up in a
** 'running - waiting for end of transmission' state. This means that we
** have to perक्रमm a chip soft reset to ensure that we can synchronize
** the hardware and software and make any media probes using a loopback
** packet meaningful.
*/
अटल व्योम
de4x5_save_skbs(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 omr;

    अगर (!lp->cache.save_cnt) अणु
	STOP_DE4X5;
	de4x5_tx(dev);                          /* Flush any sent skb's */
	de4x5_मुक्त_tx_buffs(dev);
	de4x5_cache_state(dev, DE4X5_SAVE_STATE);
	de4x5_sw_reset(dev);
	de4x5_cache_state(dev, DE4X5_RESTORE_STATE);
	lp->cache.save_cnt++;
	START_DE4X5;
    पूर्ण
पूर्ण

अटल व्योम
de4x5_rst_desc_ring(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक i;
    s32 omr;

    अगर (lp->cache.save_cnt) अणु
	STOP_DE4X5;
	outl(lp->dma_rings, DE4X5_RRBA);
	outl(lp->dma_rings + NUM_RX_DESC * माप(काष्ठा de4x5_desc),
	     DE4X5_TRBA);

	lp->rx_new = lp->rx_old = 0;
	lp->tx_new = lp->tx_old = 0;

	क्रम (i = 0; i < lp->rxRingSize; i++) अणु
	    lp->rx_ring[i].status = cpu_to_le32(R_OWN);
	पूर्ण

	क्रम (i = 0; i < lp->txRingSize; i++) अणु
	    lp->tx_ring[i].status = cpu_to_le32(0);
	पूर्ण

	barrier();
	lp->cache.save_cnt--;
	START_DE4X5;
    पूर्ण
पूर्ण

अटल व्योम
de4x5_cache_state(काष्ठा net_device *dev, पूर्णांक flag)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    चयन(flag) अणु
      हाल DE4X5_SAVE_STATE:
	lp->cache.csr0 = inl(DE4X5_BMR);
	lp->cache.csr6 = (inl(DE4X5_OMR) & ~(OMR_ST | OMR_SR));
	lp->cache.csr7 = inl(DE4X5_IMR);
	अवरोध;

      हाल DE4X5_RESTORE_STATE:
	outl(lp->cache.csr0, DE4X5_BMR);
	outl(lp->cache.csr6, DE4X5_OMR);
	outl(lp->cache.csr7, DE4X5_IMR);
	अगर (lp->chipset == DC21140) अणु
	    gep_wr(lp->cache.gepc, dev);
	    gep_wr(lp->cache.gep, dev);
	पूर्ण अन्यथा अणु
	    reset_init_sia(dev, lp->cache.csr13, lp->cache.csr14,
			                                      lp->cache.csr15);
	पूर्ण
	अवरोध;
    पूर्ण
पूर्ण

अटल व्योम
de4x5_put_cache(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    __skb_queue_tail(&lp->cache.queue, skb);
पूर्ण

अटल व्योम
de4x5_putb_cache(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    __skb_queue_head(&lp->cache.queue, skb);
पूर्ण

अटल काष्ठा sk_buff *
de4x5_get_cache(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    वापस __skb_dequeue(&lp->cache.queue);
पूर्ण

/*
** Check the Auto Negotiation State. Return OK when a link pass पूर्णांकerrupt
** is received and the स्वतः-negotiation status is NWAY OK.
*/
अटल पूर्णांक
test_ans(काष्ठा net_device *dev, s32 irqs, s32 irq_mask, s32 msec)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 sts, ans;

    अगर (lp->समयout < 0) अणु
	lp->समयout = msec/100;
	outl(irq_mask, DE4X5_IMR);

	/* clear all pending पूर्णांकerrupts */
	sts = inl(DE4X5_STS);
	outl(sts, DE4X5_STS);
    पूर्ण

    ans = inl(DE4X5_SISR) & SISR_ANS;
    sts = inl(DE4X5_STS) & ~TIMER_CB;

    अगर (!(sts & irqs) && (ans ^ ANS_NWOK) && --lp->समयout) अणु
	sts = 100 | TIMER_CB;
    पूर्ण अन्यथा अणु
	lp->समयout = -1;
    पूर्ण

    वापस sts;
पूर्ण

अटल व्योम
de4x5_setup_पूर्णांकr(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 imr, sts;

    अगर (inl(DE4X5_OMR) & OMR_SR) अणु   /* Only unmask अगर TX/RX is enabled */
	imr = 0;
	UNMASK_IRQs;
	sts = inl(DE4X5_STS);        /* Reset any pending (stale) पूर्णांकerrupts */
	outl(sts, DE4X5_STS);
	ENABLE_IRQs;
    पूर्ण
पूर्ण

/*
**
*/
अटल व्योम
reset_init_sia(काष्ठा net_device *dev, s32 csr13, s32 csr14, s32 csr15)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    RESET_SIA;
    अगर (lp->useSROM) अणु
	अगर (lp->ibn == 3) अणु
	    srom_exec(dev, lp->phy[lp->active].rst);
	    srom_exec(dev, lp->phy[lp->active].gep);
	    outl(1, DE4X5_SICR);
	    वापस;
	पूर्ण अन्यथा अणु
	    csr15 = lp->cache.csr15;
	    csr14 = lp->cache.csr14;
	    csr13 = lp->cache.csr13;
	    outl(csr15 | lp->cache.gepc, DE4X5_SIGR);
	    outl(csr15 | lp->cache.gep, DE4X5_SIGR);
	पूर्ण
    पूर्ण अन्यथा अणु
	outl(csr15, DE4X5_SIGR);
    पूर्ण
    outl(csr14, DE4X5_STRR);
    outl(csr13, DE4X5_SICR);

    mdelay(10);
पूर्ण

/*
** Create a loopback ethernet packet
*/
अटल व्योम
create_packet(काष्ठा net_device *dev, अक्षर *frame, पूर्णांक len)
अणु
    पूर्णांक i;
    अक्षर *buf = frame;

    क्रम (i=0; i<ETH_ALEN; i++) अणु             /* Use this source address */
	*buf++ = dev->dev_addr[i];
    पूर्ण
    क्रम (i=0; i<ETH_ALEN; i++) अणु             /* Use this destination address */
	*buf++ = dev->dev_addr[i];
    पूर्ण

    *buf++ = 0;                              /* Packet length (2 bytes) */
    *buf++ = 1;
पूर्ण

/*
** Look क्रम a particular board name in the EISA configuration space
*/
अटल पूर्णांक
EISA_signature(अक्षर *name, काष्ठा device *device)
अणु
    पूर्णांक i, status = 0, siglen = ARRAY_SIZE(de4x5_signatures);
    काष्ठा eisa_device *edev;

    *name = '\0';
    edev = to_eisa_device (device);
    i = edev->id.driver_data;

    अगर (i >= 0 && i < siglen) अणु
	    म_नकल (name, de4x5_signatures[i]);
	    status = 1;
    पूर्ण

    वापस status;                         /* वापस the device name string */
पूर्ण

/*
** Look क्रम a particular board name in the PCI configuration space
*/
अटल व्योम
PCI_signature(अक्षर *name, काष्ठा de4x5_निजी *lp)
अणु
    पूर्णांक i, siglen = ARRAY_SIZE(de4x5_signatures);

    अगर (lp->chipset == DC21040) अणु
	म_नकल(name, "DE434/5");
	वापस;
    पूर्ण अन्यथा अणु                           /* Search क्रम a DEC name in the SROM */
	पूर्णांक पंचांगp = *((अक्षर *)&lp->srom + 19) * 3;
	म_नकलन(name, (अक्षर *)&lp->srom + 26 + पंचांगp, 8);
    पूर्ण
    name[8] = '\0';
    क्रम (i=0; i<siglen; i++) अणु
	अगर (म_माला(name,de4x5_signatures[i])!=शून्य) अवरोध;
    पूर्ण
    अगर (i == siglen) अणु
	अगर (dec_only) अणु
	    *name = '\0';
	पूर्ण अन्यथा अणु                        /* Use chip name to aव्योम confusion */
	    म_नकल(name, (((lp->chipset == DC21040) ? "DC21040" :
			   ((lp->chipset == DC21041) ? "DC21041" :
			    ((lp->chipset == DC21140) ? "DC21140" :
			     ((lp->chipset == DC21142) ? "DC21142" :
			      ((lp->chipset == DC21143) ? "DC21143" : "UNKNOWN"
			     )))))));
	पूर्ण
	अगर (lp->chipset != DC21041) अणु
	    lp->useSROM = true;             /* card is not recognisably DEC */
	पूर्ण
    पूर्ण अन्यथा अगर ((lp->chipset & ~0x00ff) == DC2114x) अणु
	lp->useSROM = true;
    पूर्ण
पूर्ण

/*
** Set up the Ethernet PROM counter to the start of the Ethernet address on
** the DC21040, अन्यथा  पढ़ो the SROM क्रम the other chips.
** The SROM may not be present in a multi-MAC card, so first पढ़ो the
** MAC address and check क्रम a bad address. If there is a bad one then निकास
** immediately with the prior srom contents पूर्णांकact (the h/w address will
** be fixed up later).
*/
अटल व्योम
DevicePresent(काष्ठा net_device *dev, u_दीर्घ aprom_addr)
अणु
    पूर्णांक i, j=0;
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    अगर (lp->chipset == DC21040) अणु
	अगर (lp->bus == EISA) अणु
	    enet_addr_rst(aprom_addr); /* Reset Ethernet Address ROM Poपूर्णांकer */
	पूर्ण अन्यथा अणु
	    outl(0, aprom_addr);       /* Reset Ethernet Address ROM Poपूर्णांकer */
	पूर्ण
    पूर्ण अन्यथा अणु                           /* Read new srom */
	u_लघु पंचांगp;
	__le16 *p = (__le16 *)((अक्षर *)&lp->srom + SROM_HWADD);
	क्रम (i=0; i<(ETH_ALEN>>1); i++) अणु
	    पंचांगp = srom_rd(aprom_addr, (SROM_HWADD>>1) + i);
	    j += पंचांगp;	/* क्रम check क्रम 0:0:0:0:0:0 or ff:ff:ff:ff:ff:ff */
	    *p = cpu_to_le16(पंचांगp);
	पूर्ण
	अगर (j == 0 || j == 3 * 0xffff) अणु
		/* could get 0 only from all-0 and 3 * 0xffff only from all-1 */
		वापस;
	पूर्ण

	p = (__le16 *)&lp->srom;
	क्रम (i=0; i<(माप(काष्ठा de4x5_srom)>>1); i++) अणु
	    पंचांगp = srom_rd(aprom_addr, i);
	    *p++ = cpu_to_le16(पंचांगp);
	पूर्ण
	de4x5_dbg_srom(&lp->srom);
    पूर्ण
पूर्ण

/*
** Since the ग_लिखो on the Enet PROM रेजिस्टर करोesn't seem to reset the PROM
** poपूर्णांकer correctly (at least on my DE425 EISA card), this routine should करो
** it...from depca.c.
*/
अटल व्योम
enet_addr_rst(u_दीर्घ aprom_addr)
अणु
    जोड़ अणु
	काष्ठा अणु
	    u32 a;
	    u32 b;
	पूर्ण llsig;
	अक्षर Sig[माप(u32) << 1];
    पूर्ण dev;
    लघु sigLength=0;
    s8 data;
    पूर्णांक i, j;

    dev.llsig.a = ETH_PROM_SIG;
    dev.llsig.b = ETH_PROM_SIG;
    sigLength = माप(u32) << 1;

    क्रम (i=0,j=0;j<sigLength && i<PROBE_LENGTH+sigLength-1;i++) अणु
	data = inb(aprom_addr);
	अगर (dev.Sig[j] == data) अणु    /* track signature */
	    j++;
	पूर्ण अन्यथा अणु                     /* lost signature; begin search again */
	    अगर (data == dev.Sig[0]) अणु  /* rare हाल.... */
		j=1;
	    पूर्ण अन्यथा अणु
		j=0;
	    पूर्ण
	पूर्ण
    पूर्ण
पूर्ण

/*
** For the bad status हाल and no SROM, then add one to the previous
** address. However, need to add one backwards in हाल we have 0xff
** as one or more of the bytes. Only the last 3 bytes should be checked
** as the first three are invariant - asचिन्हित to an organisation.
*/
अटल पूर्णांक
get_hw_addr(काष्ठा net_device *dev)
अणु
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक broken, i, k, पंचांगp, status = 0;
    u_लघु j,chksum;
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    broken = de4x5_bad_srom(lp);

    क्रम (i=0,k=0,j=0;j<3;j++) अणु
	k <<= 1;
	अगर (k > 0xffff) k-=0xffff;

	अगर (lp->bus == PCI) अणु
	    अगर (lp->chipset == DC21040) अणु
		जबतक ((पंचांगp = inl(DE4X5_APROM)) < 0);
		k += (u_अक्षर) पंचांगp;
		dev->dev_addr[i++] = (u_अक्षर) पंचांगp;
		जबतक ((पंचांगp = inl(DE4X5_APROM)) < 0);
		k += (u_लघु) (पंचांगp << 8);
		dev->dev_addr[i++] = (u_अक्षर) पंचांगp;
	    पूर्ण अन्यथा अगर (!broken) अणु
		dev->dev_addr[i] = (u_अक्षर) lp->srom.ieee_addr[i]; i++;
		dev->dev_addr[i] = (u_अक्षर) lp->srom.ieee_addr[i]; i++;
	    पूर्ण अन्यथा अगर ((broken == SMC) || (broken == ACCTON)) अणु
		dev->dev_addr[i] = *((u_अक्षर *)&lp->srom + i); i++;
		dev->dev_addr[i] = *((u_अक्षर *)&lp->srom + i); i++;
	    पूर्ण
	पूर्ण अन्यथा अणु
	    k += (u_अक्षर) (पंचांगp = inb(EISA_APROM));
	    dev->dev_addr[i++] = (u_अक्षर) पंचांगp;
	    k += (u_लघु) ((पंचांगp = inb(EISA_APROM)) << 8);
	    dev->dev_addr[i++] = (u_अक्षर) पंचांगp;
	पूर्ण

	अगर (k > 0xffff) k-=0xffff;
    पूर्ण
    अगर (k == 0xffff) k=0;

    अगर (lp->bus == PCI) अणु
	अगर (lp->chipset == DC21040) अणु
	    जबतक ((पंचांगp = inl(DE4X5_APROM)) < 0);
	    chksum = (u_अक्षर) पंचांगp;
	    जबतक ((पंचांगp = inl(DE4X5_APROM)) < 0);
	    chksum |= (u_लघु) (पंचांगp << 8);
	    अगर ((k != chksum) && (dec_only)) status = -1;
	पूर्ण
    पूर्ण अन्यथा अणु
	chksum = (u_अक्षर) inb(EISA_APROM);
	chksum |= (u_लघु) (inb(EISA_APROM) << 8);
	अगर ((k != chksum) && (dec_only)) status = -1;
    पूर्ण

    /* If possible, try to fix a broken card - SMC only so far */
    srom_repair(dev, broken);

#अगर_घोषित CONFIG_PPC_PMAC
    /*
    ** If the address starts with 00 a0, we have to bit-reverse
    ** each byte of the address.
    */
    अगर ( machine_is(घातermac) &&
	 (dev->dev_addr[0] == 0) &&
	 (dev->dev_addr[1] == 0xa0) )
    अणु
	    क्रम (i = 0; i < ETH_ALEN; ++i)
	    अणु
		    पूर्णांक x = dev->dev_addr[i];
		    x = ((x & 0xf) << 4) + ((x & 0xf0) >> 4);
		    x = ((x & 0x33) << 2) + ((x & 0xcc) >> 2);
		    dev->dev_addr[i] = ((x & 0x55) << 1) + ((x & 0xaa) >> 1);
	    पूर्ण
    पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

    /* Test क्रम a bad enet address */
    status = test_bad_enet(dev, status);

    वापस status;
पूर्ण

/*
** Test क्रम enet addresses in the first 32 bytes.
*/
अटल पूर्णांक
de4x5_bad_srom(काष्ठा de4x5_निजी *lp)
अणु
    पूर्णांक i, status = 0;

    क्रम (i = 0; i < ARRAY_SIZE(enet_det); i++) अणु
	अगर (!स_भेद(&lp->srom, &enet_det[i], 3) &&
	    !स_भेद((अक्षर *)&lp->srom+0x10, &enet_det[i], 3)) अणु
	    अगर (i == 0) अणु
		status = SMC;
	    पूर्ण अन्यथा अगर (i == 1) अणु
		status = ACCTON;
	    पूर्ण
	    अवरोध;
	पूर्ण
    पूर्ण

    वापस status;
पूर्ण

अटल व्योम
srom_repair(काष्ठा net_device *dev, पूर्णांक card)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    चयन(card) अणु
      हाल SMC:
	स_रखो((अक्षर *)&lp->srom, 0, माप(काष्ठा de4x5_srom));
	स_नकल(lp->srom.ieee_addr, (अक्षर *)dev->dev_addr, ETH_ALEN);
	स_नकल(lp->srom.info, (अक्षर *)&srom_repair_info[SMC-1], 100);
	lp->useSROM = true;
	अवरोध;
    पूर्ण
पूर्ण

/*
** Assume that the irq's करो not follow the PCI spec - this is seems
** to be true so far (2 क्रम 2).
*/
अटल पूर्णांक
test_bad_enet(काष्ठा net_device *dev, पूर्णांक status)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक i, पंचांगp;

    क्रम (पंचांगp=0,i=0; i<ETH_ALEN; i++) पंचांगp += (u_अक्षर)dev->dev_addr[i];
    अगर ((पंचांगp == 0) || (पंचांगp == 0x5fa)) अणु
	अगर ((lp->chipset == last.chipset) &&
	    (lp->bus_num == last.bus) && (lp->bus_num > 0)) अणु
	    क्रम (i=0; i<ETH_ALEN; i++) dev->dev_addr[i] = last.addr[i];
	    क्रम (i=ETH_ALEN-1; i>2; --i) अणु
		dev->dev_addr[i] += 1;
		अगर (dev->dev_addr[i] != 0) अवरोध;
	    पूर्ण
	    क्रम (i=0; i<ETH_ALEN; i++) last.addr[i] = dev->dev_addr[i];
	    अगर (!an_exception(lp)) अणु
		dev->irq = last.irq;
	    पूर्ण

	    status = 0;
	पूर्ण
    पूर्ण अन्यथा अगर (!status) अणु
	last.chipset = lp->chipset;
	last.bus = lp->bus_num;
	last.irq = dev->irq;
	क्रम (i=0; i<ETH_ALEN; i++) last.addr[i] = dev->dev_addr[i];
    पूर्ण

    वापस status;
पूर्ण

/*
** List of board exceptions with correctly wired IRQs
*/
अटल पूर्णांक
an_exception(काष्ठा de4x5_निजी *lp)
अणु
    अगर ((*(u_लघु *)lp->srom.sub_venकरोr_id == 0x00c0) &&
	(*(u_लघु *)lp->srom.sub_प्रणाली_id == 0x95e0)) अणु
	वापस -1;
    पूर्ण

    वापस 0;
पूर्ण

/*
** SROM Read
*/
अटल लघु
srom_rd(u_दीर्घ addr, u_अक्षर offset)
अणु
    sendto_srom(SROM_RD | SROM_SR, addr);

    srom_latch(SROM_RD | SROM_SR | DT_CS, addr);
    srom_command(SROM_RD | SROM_SR | DT_IN | DT_CS, addr);
    srom_address(SROM_RD | SROM_SR | DT_CS, addr, offset);

    वापस srom_data(SROM_RD | SROM_SR | DT_CS, addr);
पूर्ण

अटल व्योम
srom_latch(u_पूर्णांक command, u_दीर्घ addr)
अणु
    sendto_srom(command, addr);
    sendto_srom(command | DT_CLK, addr);
    sendto_srom(command, addr);
पूर्ण

अटल व्योम
srom_command(u_पूर्णांक command, u_दीर्घ addr)
अणु
    srom_latch(command, addr);
    srom_latch(command, addr);
    srom_latch((command & 0x0000ff00) | DT_CS, addr);
पूर्ण

अटल व्योम
srom_address(u_पूर्णांक command, u_दीर्घ addr, u_अक्षर offset)
अणु
    पूर्णांक i, a;

    a = offset << 2;
    क्रम (i=0; i<6; i++, a <<= 1) अणु
	srom_latch(command | ((a & 0x80) ? DT_IN : 0), addr);
    पूर्ण
    udelay(1);

    i = (getfrom_srom(addr) >> 3) & 0x01;
पूर्ण

अटल लघु
srom_data(u_पूर्णांक command, u_दीर्घ addr)
अणु
    पूर्णांक i;
    लघु word = 0;
    s32 पंचांगp;

    क्रम (i=0; i<16; i++) अणु
	sendto_srom(command  | DT_CLK, addr);
	पंचांगp = getfrom_srom(addr);
	sendto_srom(command, addr);

	word = (word << 1) | ((पंचांगp >> 3) & 0x01);
    पूर्ण

    sendto_srom(command & 0x0000ff00, addr);

    वापस word;
पूर्ण

/*
अटल व्योम
srom_busy(u_पूर्णांक command, u_दीर्घ addr)
अणु
   sendto_srom((command & 0x0000ff00) | DT_CS, addr);

   जबतक (!((getfrom_srom(addr) >> 3) & 0x01)) अणु
       mdelay(1);
   पूर्ण

   sendto_srom(command & 0x0000ff00, addr);
पूर्ण
*/

अटल व्योम
sendto_srom(u_पूर्णांक command, u_दीर्घ addr)
अणु
    outl(command, addr);
    udelay(1);
पूर्ण

अटल पूर्णांक
getfrom_srom(u_दीर्घ addr)
अणु
    s32 पंचांगp;

    पंचांगp = inl(addr);
    udelay(1);

    वापस पंचांगp;
पूर्ण

अटल पूर्णांक
srom_infoleaf_info(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक i, count;
    u_अक्षर *p;

    /* Find the infoleaf decoder function that matches this chipset */
    क्रम (i=0; i<INFOLEAF_SIZE; i++) अणु
	अगर (lp->chipset == infoleaf_array[i].chipset) अवरोध;
    पूर्ण
    अगर (i == INFOLEAF_SIZE) अणु
	lp->useSROM = false;
	prपूर्णांकk("%s: Cannot find correct chipset for SROM decoding!\n",
	                                                          dev->name);
	वापस -ENXIO;
    पूर्ण

    lp->infoleaf_fn = infoleaf_array[i].fn;

    /* Find the inक्रमmation offset that this function should use */
    count = *((u_अक्षर *)&lp->srom + 19);
    p  = (u_अक्षर *)&lp->srom + 26;

    अगर (count > 1) अणु
	क्रम (i=count; i; --i, p+=3) अणु
	    अगर (lp->device == *p) अवरोध;
	पूर्ण
	अगर (i == 0) अणु
	    lp->useSROM = false;
	    prपूर्णांकk("%s: Cannot find correct PCI device [%d] for SROM decoding!\n",
	                                               dev->name, lp->device);
	    वापस -ENXIO;
	पूर्ण
    पूर्ण

	lp->infoleaf_offset = get_unaligned_le16(p + 1);

    वापस 0;
पूर्ण

/*
** This routine loads any type 1 or 3 MII info पूर्णांकo the mii device
** काष्ठा and executes any type 5 code to reset PHY devices क्रम this
** controller.
** The info क्रम the MII devices will be valid since the index used
** will follow the discovery process from MII address 1-31 then 0.
*/
अटल व्योम
srom_init(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर *p = (u_अक्षर *)&lp->srom + lp->infoleaf_offset;
    u_अक्षर count;

    p+=2;
    अगर (lp->chipset == DC21140) अणु
	lp->cache.gepc = (*p++ | GEP_CTRL);
	gep_wr(lp->cache.gepc, dev);
    पूर्ण

    /* Block count */
    count = *p++;

    /* Jump the infoblocks to find types */
    क्रम (;count; --count) अणु
	अगर (*p < 128) अणु
	    p += COMPACT_LEN;
	पूर्ण अन्यथा अगर (*(p+1) == 5) अणु
	    type5_infoblock(dev, 1, p);
	    p += ((*p & BLOCK_LEN) + 1);
	पूर्ण अन्यथा अगर (*(p+1) == 4) अणु
	    p += ((*p & BLOCK_LEN) + 1);
	पूर्ण अन्यथा अगर (*(p+1) == 3) अणु
	    type3_infoblock(dev, 1, p);
	    p += ((*p & BLOCK_LEN) + 1);
	पूर्ण अन्यथा अगर (*(p+1) == 2) अणु
	    p += ((*p & BLOCK_LEN) + 1);
	पूर्ण अन्यथा अगर (*(p+1) == 1) अणु
	    type1_infoblock(dev, 1, p);
	    p += ((*p & BLOCK_LEN) + 1);
	पूर्ण अन्यथा अणु
	    p += ((*p & BLOCK_LEN) + 1);
	पूर्ण
    पूर्ण
पूर्ण

/*
** A generic routine that ग_लिखोs GEP control, data and reset inक्रमmation
** to the GEP रेजिस्टर (21140) or csr15 GEP portion (2114[23]).
*/
अटल व्योम
srom_exec(काष्ठा net_device *dev, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    u_अक्षर count = (p ? *p++ : 0);
    u_लघु *w = (u_लघु *)p;

    अगर (((lp->ibn != 1) && (lp->ibn != 3) && (lp->ibn != 5)) || !count) वापस;

    अगर (lp->chipset != DC21140) RESET_SIA;

    जबतक (count--) अणु
	gep_wr(((lp->chipset==DC21140) && (lp->ibn!=5) ?
		                                   *p++ : get_unaligned_le16(w++)), dev);
	mdelay(2);                          /* 2ms per action */
    पूर्ण

    अगर (lp->chipset != DC21140) अणु
	outl(lp->cache.csr14, DE4X5_STRR);
	outl(lp->cache.csr13, DE4X5_SICR);
    पूर्ण
पूर्ण

/*
** Basically this function is a NOP since it will never be called,
** unless I implement the DC21041 SROM functions. There's no need
** since the existing code will be satisfactory क्रम all boards.
*/
अटल पूर्णांक
dc21041_infoleaf(काष्ठा net_device *dev)
अणु
    वापस DE4X5_AUTOSENSE_MS;
पूर्ण

अटल पूर्णांक
dc21140_infoleaf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर count = 0;
    u_अक्षर *p = (u_अक्षर *)&lp->srom + lp->infoleaf_offset;
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;

    /* Read the connection type */
    p+=2;

    /* GEP control */
    lp->cache.gepc = (*p++ | GEP_CTRL);

    /* Block count */
    count = *p++;

    /* Recursively figure out the info blocks */
    अगर (*p < 128) अणु
	next_tick = dc_infoblock[COMPACT](dev, count, p);
    पूर्ण अन्यथा अणु
	next_tick = dc_infoblock[*(p+1)](dev, count, p);
    पूर्ण

    अगर (lp->tcount == count) अणु
	lp->media = NC;
        अगर (lp->media != lp->c_media) अणु
	    de4x5_dbg_media(dev);
	    lp->c_media = lp->media;
	पूर्ण
	lp->media = INIT;
	lp->tcount = 0;
	lp->tx_enable = false;
    पूर्ण

    वापस next_tick & ~TIMER_CB;
पूर्ण

अटल पूर्णांक
dc21142_infoleaf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर count = 0;
    u_अक्षर *p = (u_अक्षर *)&lp->srom + lp->infoleaf_offset;
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;

    /* Read the connection type */
    p+=2;

    /* Block count */
    count = *p++;

    /* Recursively figure out the info blocks */
    अगर (*p < 128) अणु
	next_tick = dc_infoblock[COMPACT](dev, count, p);
    पूर्ण अन्यथा अणु
	next_tick = dc_infoblock[*(p+1)](dev, count, p);
    पूर्ण

    अगर (lp->tcount == count) अणु
	lp->media = NC;
        अगर (lp->media != lp->c_media) अणु
	    de4x5_dbg_media(dev);
	    lp->c_media = lp->media;
	पूर्ण
	lp->media = INIT;
	lp->tcount = 0;
	lp->tx_enable = false;
    पूर्ण

    वापस next_tick & ~TIMER_CB;
पूर्ण

अटल पूर्णांक
dc21143_infoleaf(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर count = 0;
    u_अक्षर *p = (u_अक्षर *)&lp->srom + lp->infoleaf_offset;
    पूर्णांक next_tick = DE4X5_AUTOSENSE_MS;

    /* Read the connection type */
    p+=2;

    /* Block count */
    count = *p++;

    /* Recursively figure out the info blocks */
    अगर (*p < 128) अणु
	next_tick = dc_infoblock[COMPACT](dev, count, p);
    पूर्ण अन्यथा अणु
	next_tick = dc_infoblock[*(p+1)](dev, count, p);
    पूर्ण
    अगर (lp->tcount == count) अणु
	lp->media = NC;
        अगर (lp->media != lp->c_media) अणु
	    de4x5_dbg_media(dev);
	    lp->c_media = lp->media;
	पूर्ण
	lp->media = INIT;
	lp->tcount = 0;
	lp->tx_enable = false;
    पूर्ण

    वापस next_tick & ~TIMER_CB;
पूर्ण

/*
** The compact infoblock is only deचिन्हित क्रम DC21140[A] chips, so
** we'll reuse the dc21140m_स्वतःconf function. Non MII media only.
*/
अटल पूर्णांक
compact_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर flags, csr6;

    /* Recursively figure out the info blocks */
    अगर (--count > lp->tcount) अणु
	अगर (*(p+COMPACT_LEN) < 128) अणु
	    वापस dc_infoblock[COMPACT](dev, count, p+COMPACT_LEN);
	पूर्ण अन्यथा अणु
	    वापस dc_infoblock[*(p+COMPACT_LEN+1)](dev, count, p+COMPACT_LEN);
	पूर्ण
    पूर्ण

    अगर ((lp->media == INIT) && (lp->समयout < 0)) अणु
        lp->ibn = COMPACT;
        lp->active = 0;
	gep_wr(lp->cache.gepc, dev);
	lp->infoblock_media = (*p++) & COMPACT_MC;
	lp->cache.gep = *p++;
	csr6 = *p++;
	flags = *p++;

	lp->asBitValid = (flags & 0x80) ? 0 : -1;
	lp->defMedium = (flags & 0x40) ? -1 : 0;
	lp->asBit = 1 << ((csr6 >> 1) & 0x07);
	lp->asPolarity = ((csr6 & 0x80) ? -1 : 0) & lp->asBit;
	lp->infoblock_csr6 = OMR_DEF | ((csr6 & 0x71) << 18);
	lp->useMII = false;

	de4x5_चयन_mac_port(dev);
    पूर्ण

    वापस dc21140m_स्वतःconf(dev);
पूर्ण

/*
** This block describes non MII media क्रम the DC21140[A] only.
*/
अटल पूर्णांक
type0_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर flags, csr6, len = (*p & BLOCK_LEN)+1;

    /* Recursively figure out the info blocks */
    अगर (--count > lp->tcount) अणु
	अगर (*(p+len) < 128) अणु
	    वापस dc_infoblock[COMPACT](dev, count, p+len);
	पूर्ण अन्यथा अणु
	    वापस dc_infoblock[*(p+len+1)](dev, count, p+len);
	पूर्ण
    पूर्ण

    अगर ((lp->media == INIT) && (lp->समयout < 0)) अणु
        lp->ibn = 0;
        lp->active = 0;
        gep_wr(lp->cache.gepc, dev);
	p+=2;
	lp->infoblock_media = (*p++) & BLOCK0_MC;
	lp->cache.gep = *p++;
	csr6 = *p++;
	flags = *p++;

	lp->asBitValid = (flags & 0x80) ? 0 : -1;
	lp->defMedium = (flags & 0x40) ? -1 : 0;
	lp->asBit = 1 << ((csr6 >> 1) & 0x07);
	lp->asPolarity = ((csr6 & 0x80) ? -1 : 0) & lp->asBit;
	lp->infoblock_csr6 = OMR_DEF | ((csr6 & 0x71) << 18);
	lp->useMII = false;

	de4x5_चयन_mac_port(dev);
    पूर्ण

    वापस dc21140m_स्वतःconf(dev);
पूर्ण

/* These functions are under स्थिरruction! */

अटल पूर्णांक
type1_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर len = (*p & BLOCK_LEN)+1;

    /* Recursively figure out the info blocks */
    अगर (--count > lp->tcount) अणु
	अगर (*(p+len) < 128) अणु
	    वापस dc_infoblock[COMPACT](dev, count, p+len);
	पूर्ण अन्यथा अणु
	    वापस dc_infoblock[*(p+len+1)](dev, count, p+len);
	पूर्ण
    पूर्ण

    p += 2;
    अगर (lp->state == INITIALISED) अणु
        lp->ibn = 1;
	lp->active = *p++;
	lp->phy[lp->active].gep = (*p ? p : शून्य); p += (*p + 1);
	lp->phy[lp->active].rst = (*p ? p : शून्य); p += (*p + 1);
	lp->phy[lp->active].mc  = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].ana = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].fdx = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].tपंचांग = get_unaligned_le16(p);
	वापस 0;
    पूर्ण अन्यथा अगर ((lp->media == INIT) && (lp->समयout < 0)) अणु
        lp->ibn = 1;
        lp->active = *p;
	lp->infoblock_csr6 = OMR_MII_100;
	lp->useMII = true;
	lp->infoblock_media = ANS;

	de4x5_चयन_mac_port(dev);
    पूर्ण

    वापस dc21140m_स्वतःconf(dev);
पूर्ण

अटल पूर्णांक
type2_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर len = (*p & BLOCK_LEN)+1;

    /* Recursively figure out the info blocks */
    अगर (--count > lp->tcount) अणु
	अगर (*(p+len) < 128) अणु
	    वापस dc_infoblock[COMPACT](dev, count, p+len);
	पूर्ण अन्यथा अणु
	    वापस dc_infoblock[*(p+len+1)](dev, count, p+len);
	पूर्ण
    पूर्ण

    अगर ((lp->media == INIT) && (lp->समयout < 0)) अणु
        lp->ibn = 2;
        lp->active = 0;
	p += 2;
	lp->infoblock_media = (*p) & MEDIA_CODE;

        अगर ((*p++) & EXT_FIELD) अणु
	    lp->cache.csr13 = get_unaligned_le16(p); p += 2;
	    lp->cache.csr14 = get_unaligned_le16(p); p += 2;
	    lp->cache.csr15 = get_unaligned_le16(p); p += 2;
	पूर्ण अन्यथा अणु
	    lp->cache.csr13 = CSR13;
	    lp->cache.csr14 = CSR14;
	    lp->cache.csr15 = CSR15;
	पूर्ण
        lp->cache.gepc = ((s32)(get_unaligned_le16(p)) << 16); p += 2;
        lp->cache.gep  = ((s32)(get_unaligned_le16(p)) << 16);
	lp->infoblock_csr6 = OMR_SIA;
	lp->useMII = false;

	de4x5_चयन_mac_port(dev);
    पूर्ण

    वापस dc2114x_स्वतःconf(dev);
पूर्ण

अटल पूर्णांक
type3_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर len = (*p & BLOCK_LEN)+1;

    /* Recursively figure out the info blocks */
    अगर (--count > lp->tcount) अणु
	अगर (*(p+len) < 128) अणु
	    वापस dc_infoblock[COMPACT](dev, count, p+len);
	पूर्ण अन्यथा अणु
	    वापस dc_infoblock[*(p+len+1)](dev, count, p+len);
	पूर्ण
    पूर्ण

    p += 2;
    अगर (lp->state == INITIALISED) अणु
        lp->ibn = 3;
        lp->active = *p++;
	अगर (MOTO_SROM_BUG) lp->active = 0;
	lp->phy[lp->active].gep = (*p ? p : शून्य); p += (2 * (*p) + 1);
	lp->phy[lp->active].rst = (*p ? p : शून्य); p += (2 * (*p) + 1);
	lp->phy[lp->active].mc  = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].ana = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].fdx = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].tपंचांग = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].mci = *p;
	वापस 0;
    पूर्ण अन्यथा अगर ((lp->media == INIT) && (lp->समयout < 0)) अणु
        lp->ibn = 3;
	lp->active = *p;
	अगर (MOTO_SROM_BUG) lp->active = 0;
	lp->infoblock_csr6 = OMR_MII_100;
	lp->useMII = true;
	lp->infoblock_media = ANS;

	de4x5_चयन_mac_port(dev);
    पूर्ण

    वापस dc2114x_स्वतःconf(dev);
पूर्ण

अटल पूर्णांक
type4_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर flags, csr6, len = (*p & BLOCK_LEN)+1;

    /* Recursively figure out the info blocks */
    अगर (--count > lp->tcount) अणु
	अगर (*(p+len) < 128) अणु
	    वापस dc_infoblock[COMPACT](dev, count, p+len);
	पूर्ण अन्यथा अणु
	    वापस dc_infoblock[*(p+len+1)](dev, count, p+len);
	पूर्ण
    पूर्ण

    अगर ((lp->media == INIT) && (lp->समयout < 0)) अणु
        lp->ibn = 4;
        lp->active = 0;
	p+=2;
	lp->infoblock_media = (*p++) & MEDIA_CODE;
        lp->cache.csr13 = CSR13;              /* Hard coded शेषs */
	lp->cache.csr14 = CSR14;
	lp->cache.csr15 = CSR15;
        lp->cache.gepc = ((s32)(get_unaligned_le16(p)) << 16); p += 2;
        lp->cache.gep  = ((s32)(get_unaligned_le16(p)) << 16); p += 2;
	csr6 = *p++;
	flags = *p++;

	lp->asBitValid = (flags & 0x80) ? 0 : -1;
	lp->defMedium = (flags & 0x40) ? -1 : 0;
	lp->asBit = 1 << ((csr6 >> 1) & 0x07);
	lp->asPolarity = ((csr6 & 0x80) ? -1 : 0) & lp->asBit;
	lp->infoblock_csr6 = OMR_DEF | ((csr6 & 0x71) << 18);
	lp->useMII = false;

	de4x5_चयन_mac_port(dev);
    पूर्ण

    वापस dc2114x_स्वतःconf(dev);
पूर्ण

/*
** This block type provides inक्रमmation क्रम resetting बाह्यal devices
** (chips) through the General Purpose Register.
*/
अटल पूर्णांक
type5_infoblock(काष्ठा net_device *dev, u_अक्षर count, u_अक्षर *p)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_अक्षर len = (*p & BLOCK_LEN)+1;

    /* Recursively figure out the info blocks */
    अगर (--count > lp->tcount) अणु
	अगर (*(p+len) < 128) अणु
	    वापस dc_infoblock[COMPACT](dev, count, p+len);
	पूर्ण अन्यथा अणु
	    वापस dc_infoblock[*(p+len+1)](dev, count, p+len);
	पूर्ण
    पूर्ण

    /* Must be initializing to run this code */
    अगर ((lp->state == INITIALISED) || (lp->media == INIT)) अणु
	p+=2;
        lp->rst = p;
        srom_exec(dev, lp->rst);
    पूर्ण

    वापस DE4X5_AUTOSENSE_MS;
पूर्ण

/*
** MII Read/Write
*/

अटल पूर्णांक
mii_rd(u_अक्षर phyreg, u_अक्षर phyaddr, u_दीर्घ ioaddr)
अणु
    mii_wdata(MII_PREAMBLE,  2, ioaddr);   /* Start of 34 bit preamble...    */
    mii_wdata(MII_PREAMBLE, 32, ioaddr);   /* ...जारीd                   */
    mii_wdata(MII_STRD, 4, ioaddr);        /* SFD and Read operation         */
    mii_address(phyaddr, ioaddr);          /* PHY address to be accessed     */
    mii_address(phyreg, ioaddr);           /* PHY Register to पढ़ो           */
    mii_ta(MII_STRD, ioaddr);              /* Turn around समय - 2 MDC       */

    वापस mii_rdata(ioaddr);              /* Read data                      */
पूर्ण

अटल व्योम
mii_wr(पूर्णांक data, u_अक्षर phyreg, u_अक्षर phyaddr, u_दीर्घ ioaddr)
अणु
    mii_wdata(MII_PREAMBLE,  2, ioaddr);   /* Start of 34 bit preamble...    */
    mii_wdata(MII_PREAMBLE, 32, ioaddr);   /* ...जारीd                   */
    mii_wdata(MII_STWR, 4, ioaddr);        /* SFD and Write operation        */
    mii_address(phyaddr, ioaddr);          /* PHY address to be accessed     */
    mii_address(phyreg, ioaddr);           /* PHY Register to ग_लिखो          */
    mii_ta(MII_STWR, ioaddr);              /* Turn around समय - 2 MDC       */
    data = mii_swap(data, 16);             /* Swap data bit ordering         */
    mii_wdata(data, 16, ioaddr);           /* Write data                     */
पूर्ण

अटल पूर्णांक
mii_rdata(u_दीर्घ ioaddr)
अणु
    पूर्णांक i;
    s32 पंचांगp = 0;

    क्रम (i=0; i<16; i++) अणु
	पंचांगp <<= 1;
	पंचांगp |= getfrom_mii(MII_MRD | MII_RD, ioaddr);
    पूर्ण

    वापस पंचांगp;
पूर्ण

अटल व्योम
mii_wdata(पूर्णांक data, पूर्णांक len, u_दीर्घ ioaddr)
अणु
    पूर्णांक i;

    क्रम (i=0; i<len; i++) अणु
	sendto_mii(MII_MWR | MII_WR, data, ioaddr);
	data >>= 1;
    पूर्ण
पूर्ण

अटल व्योम
mii_address(u_अक्षर addr, u_दीर्घ ioaddr)
अणु
    पूर्णांक i;

    addr = mii_swap(addr, 5);
    क्रम (i=0; i<5; i++) अणु
	sendto_mii(MII_MWR | MII_WR, addr, ioaddr);
	addr >>= 1;
    पूर्ण
पूर्ण

अटल व्योम
mii_ta(u_दीर्घ rw, u_दीर्घ ioaddr)
अणु
    अगर (rw == MII_STWR) अणु
	sendto_mii(MII_MWR | MII_WR, 1, ioaddr);
	sendto_mii(MII_MWR | MII_WR, 0, ioaddr);
    पूर्ण अन्यथा अणु
	getfrom_mii(MII_MRD | MII_RD, ioaddr);        /* Tri-state MDIO */
    पूर्ण
पूर्ण

अटल पूर्णांक
mii_swap(पूर्णांक data, पूर्णांक len)
अणु
    पूर्णांक i, पंचांगp = 0;

    क्रम (i=0; i<len; i++) अणु
	पंचांगp <<= 1;
	पंचांगp |= (data & 1);
	data >>= 1;
    पूर्ण

    वापस पंचांगp;
पूर्ण

अटल व्योम
sendto_mii(u32 command, पूर्णांक data, u_दीर्घ ioaddr)
अणु
    u32 j;

    j = (data & 1) << 17;
    outl(command | j, ioaddr);
    udelay(1);
    outl(command | MII_MDC | j, ioaddr);
    udelay(1);
पूर्ण

अटल पूर्णांक
getfrom_mii(u32 command, u_दीर्घ ioaddr)
अणु
    outl(command, ioaddr);
    udelay(1);
    outl(command | MII_MDC, ioaddr);
    udelay(1);

    वापस (inl(ioaddr) >> 19) & 1;
पूर्ण

/*
** Here's 3 ways to calculate the OUI from the ID रेजिस्टरs.
*/
अटल पूर्णांक
mii_get_oui(u_अक्षर phyaddr, u_दीर्घ ioaddr)
अणु
/*
    जोड़ अणु
	u_लघु reg;
	u_अक्षर breg[2];
    पूर्ण a;
    पूर्णांक i, r2, r3, ret=0;*/
    पूर्णांक r2;

    /* Read r2 and r3 */
    r2 = mii_rd(MII_ID0, phyaddr, ioaddr);
    mii_rd(MII_ID1, phyaddr, ioaddr);
                                                /* SEEQ and Cypress way * /
    / * Shuffle r2 and r3 * /
    a.reg=0;
    r3 = ((r3>>10)|(r2<<6))&0x0ff;
    r2 = ((r2>>2)&0x3fff);

    / * Bit reverse r3 * /
    क्रम (i=0;i<8;i++) अणु
	ret<<=1;
	ret |= (r3&1);
	r3>>=1;
    पूर्ण

    / * Bit reverse r2 * /
    क्रम (i=0;i<16;i++) अणु
	a.reg<<=1;
	a.reg |= (r2&1);
	r2>>=1;
    पूर्ण

    / * Swap r2 bytes * /
    i=a.breg[0];
    a.breg[0]=a.breg[1];
    a.breg[1]=i;

    वापस (a.reg<<8)|ret; */                 /* SEEQ and Cypress way */
/*    वापस (r2<<6)|(u_पूर्णांक)(r3>>10); */      /* NATIONAL and BROADCOM way */
    वापस r2;                                  /* (I did it) My way */
पूर्ण

/*
** The SROM spec क्रमces us to search addresses [1-31 0]. Bummer.
*/
अटल पूर्णांक
mii_get_phy(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक i, j, k, n, limit=ARRAY_SIZE(phy_info);
    पूर्णांक id;

    lp->active = 0;
    lp->useMII = true;

    /* Search the MII address space क्रम possible PHY devices */
    क्रम (n=0, lp->mii_cnt=0, i=1; !((i==1) && (n==1)); i=(i+1)%DE4X5_MAX_MII) अणु
	lp->phy[lp->active].addr = i;
	अगर (i==0) n++;                             /* Count cycles */
	जबतक (de4x5_reset_phy(dev)<0) udelay(100);/* Wait क्रम reset */
	id = mii_get_oui(i, DE4X5_MII);
	अगर ((id == 0) || (id == 65535)) जारी;  /* Valid ID? */
	क्रम (j=0; j<limit; j++) अणु                  /* Search PHY table */
	    अगर (id != phy_info[j].id) जारी;    /* ID match? */
	    क्रम (k=0; k < DE4X5_MAX_PHY && lp->phy[k].id; k++);
	    अगर (k < DE4X5_MAX_PHY) अणु
		स_नकल((अक्षर *)&lp->phy[k],
		       (अक्षर *)&phy_info[j], माप(काष्ठा phy_table));
		lp->phy[k].addr = i;
		lp->mii_cnt++;
		lp->active++;
	    पूर्ण अन्यथा अणु
		जाओ purgatory;                    /* Stop the search */
	    पूर्ण
	    अवरोध;
	पूर्ण
	अगर ((j == limit) && (i < DE4X5_MAX_MII)) अणु
	    क्रम (k=0; k < DE4X5_MAX_PHY && lp->phy[k].id; k++);
	    lp->phy[k].addr = i;
	    lp->phy[k].id = id;
	    lp->phy[k].spd.reg = GENERIC_REG;      /* ANLPA रेजिस्टर         */
	    lp->phy[k].spd.mask = GENERIC_MASK;    /* 100Mb/s technologies   */
	    lp->phy[k].spd.value = GENERIC_VALUE;  /* TX & T4, H/F Duplex    */
	    lp->mii_cnt++;
	    lp->active++;
	    prपूर्णांकk("%s: Using generic MII device control. If the board doesn't operate,\nplease mail the following dump to the author:\n", dev->name);
	    j = de4x5_debug;
	    de4x5_debug |= DEBUG_MII;
	    de4x5_dbg_mii(dev, k);
	    de4x5_debug = j;
	    prपूर्णांकk("\n");
	पूर्ण
    पूर्ण
  purgatory:
    lp->active = 0;
    अगर (lp->phy[0].id) अणु                           /* Reset the PHY devices */
	क्रम (k=0; k < DE4X5_MAX_PHY && lp->phy[k].id; k++) अणु /*For each PHY*/
	    mii_wr(MII_CR_RST, MII_CR, lp->phy[k].addr, DE4X5_MII);
	    जबतक (mii_rd(MII_CR, lp->phy[k].addr, DE4X5_MII) & MII_CR_RST);

	    de4x5_dbg_mii(dev, k);
	पूर्ण
    पूर्ण
    अगर (!lp->mii_cnt) lp->useMII = false;

    वापस lp->mii_cnt;
पूर्ण

अटल अक्षर *
build_setup_frame(काष्ठा net_device *dev, पूर्णांक mode)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक i;
    अक्षर *pa = lp->setup_frame;

    /* Initialise the setup frame */
    अगर (mode == ALL) अणु
	स_रखो(lp->setup_frame, 0, SETUP_FRAME_LEN);
    पूर्ण

    अगर (lp->setup_f == HASH_PERF) अणु
	क्रम (pa=lp->setup_frame+IMPERF_PA_OFFSET, i=0; i<ETH_ALEN; i++) अणु
	    *(pa + i) = dev->dev_addr[i];                 /* Host address */
	    अगर (i & 0x01) pa += 2;
	पूर्ण
	*(lp->setup_frame + (DE4X5_HASH_TABLE_LEN >> 3) - 3) = 0x80;
    पूर्ण अन्यथा अणु
	क्रम (i=0; i<ETH_ALEN; i++) अणु /* Host address */
	    *(pa + (i&1)) = dev->dev_addr[i];
	    अगर (i & 0x01) pa += 4;
	पूर्ण
	क्रम (i=0; i<ETH_ALEN; i++) अणु /* Broadcast address */
	    *(pa + (i&1)) = (अक्षर) 0xff;
	    अगर (i & 0x01) pa += 4;
	पूर्ण
    पूर्ण

    वापस pa;                     /* Poपूर्णांकs to the next entry */
पूर्ण

अटल व्योम
disable_ast(काष्ठा net_device *dev)
अणु
	काष्ठा de4x5_निजी *lp = netdev_priv(dev);
	del_समयr_sync(&lp->समयr);
पूर्ण

अटल दीर्घ
de4x5_चयन_mac_port(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;
    s32 omr;

    STOP_DE4X5;

    /* Assert the OMR_PS bit in CSR6 */
    omr = (inl(DE4X5_OMR) & ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR |
			                                             OMR_FDX));
    omr |= lp->infoblock_csr6;
    अगर (omr & OMR_PS) omr |= OMR_HBD;
    outl(omr, DE4X5_OMR);

    /* Soft Reset */
    RESET_DE4X5;

    /* Restore the GEP - especially क्रम COMPACT and Type 0 Infoblocks */
    अगर (lp->chipset == DC21140) अणु
	gep_wr(lp->cache.gepc, dev);
	gep_wr(lp->cache.gep, dev);
    पूर्ण अन्यथा अगर ((lp->chipset & ~0x0ff) == DC2114x) अणु
	reset_init_sia(dev, lp->cache.csr13, lp->cache.csr14, lp->cache.csr15);
    पूर्ण

    /* Restore CSR6 */
    outl(omr, DE4X5_OMR);

    /* Reset CSR8 */
    inl(DE4X5_MFC);

    वापस omr;
पूर्ण

अटल व्योम
gep_wr(s32 data, काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    अगर (lp->chipset == DC21140) अणु
	outl(data, DE4X5_GEP);
    पूर्ण अन्यथा अगर ((lp->chipset & ~0x00ff) == DC2114x) अणु
	outl((data<<16) | lp->cache.csr15, DE4X5_SIGR);
    पूर्ण
पूर्ण

अटल पूर्णांक
gep_rd(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    अगर (lp->chipset == DC21140) अणु
	वापस inl(DE4X5_GEP);
    पूर्ण अन्यथा अगर ((lp->chipset & ~0x00ff) == DC2114x) अणु
	वापस inl(DE4X5_SIGR) & 0x000fffff;
    पूर्ण

    वापस 0;
पूर्ण

अटल व्योम
yawn(काष्ठा net_device *dev, पूर्णांक state)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    अगर ((lp->chipset == DC21040) || (lp->chipset == DC21140)) वापस;

    अगर(lp->bus == EISA) अणु
	चयन(state) अणु
	  हाल WAKEUP:
	    outb(WAKEUP, PCI_CFPM);
	    mdelay(10);
	    अवरोध;

	  हाल SNOOZE:
	    outb(SNOOZE, PCI_CFPM);
	    अवरोध;

	  हाल SLEEP:
	    outl(0, DE4X5_SICR);
	    outb(SLEEP, PCI_CFPM);
	    अवरोध;
	पूर्ण
    पूर्ण अन्यथा अणु
	काष्ठा pci_dev *pdev = to_pci_dev (lp->gendev);
	चयन(state) अणु
	  हाल WAKEUP:
	    pci_ग_लिखो_config_byte(pdev, PCI_CFDA_PSM, WAKEUP);
	    mdelay(10);
	    अवरोध;

	  हाल SNOOZE:
	    pci_ग_लिखो_config_byte(pdev, PCI_CFDA_PSM, SNOOZE);
	    अवरोध;

	  हाल SLEEP:
	    outl(0, DE4X5_SICR);
	    pci_ग_लिखो_config_byte(pdev, PCI_CFDA_PSM, SLEEP);
	    अवरोध;
	पूर्ण
    पूर्ण
पूर्ण

अटल व्योम
de4x5_parse_params(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    अक्षर *p, *q, t;

    lp->params.fdx = false;
    lp->params.स्वतःsense = AUTO;

    अगर (args == शून्य) वापस;

    अगर ((p = म_माला(args, dev->name))) अणु
	अगर (!(q = म_माला(p+म_माप(dev->name), "eth"))) q = p + म_माप(p);
	t = *q;
	*q = '\0';

	अगर (म_माला(p, "fdx") || म_माला(p, "FDX")) lp->params.fdx = true;

	अगर (म_माला(p, "autosense") || म_माला(p, "AUTOSENSE")) अणु
	    अगर (म_माला(p, "TP_NW")) अणु
		lp->params.स्वतःsense = TP_NW;
	    पूर्ण अन्यथा अगर (म_माला(p, "TP")) अणु
		lp->params.स्वतःsense = TP;
	    पूर्ण अन्यथा अगर (म_माला(p, "BNC_AUI")) अणु
		lp->params.स्वतःsense = BNC;
	    पूर्ण अन्यथा अगर (म_माला(p, "BNC")) अणु
		lp->params.स्वतःsense = BNC;
	    पूर्ण अन्यथा अगर (म_माला(p, "AUI")) अणु
		lp->params.स्वतःsense = AUI;
	    पूर्ण अन्यथा अगर (म_माला(p, "10Mb")) अणु
		lp->params.स्वतःsense = _10Mb;
	    पूर्ण अन्यथा अगर (म_माला(p, "100Mb")) अणु
		lp->params.स्वतःsense = _100Mb;
	    पूर्ण अन्यथा अगर (म_माला(p, "AUTO")) अणु
		lp->params.स्वतःsense = AUTO;
	    पूर्ण
	पूर्ण
	*q = t;
    पूर्ण
पूर्ण

अटल व्योम
de4x5_dbg_खोलो(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    पूर्णांक i;

    अगर (de4x5_debug & DEBUG_OPEN) अणु
	prपूर्णांकk("%s: de4x5 opening with irq %d\n",dev->name,dev->irq);
	prपूर्णांकk("\tphysical address: %pM\n", dev->dev_addr);
	prपूर्णांकk("Descriptor head addresses:\n");
	prपूर्णांकk("\t0x%8.8lx  0x%8.8lx\n",(u_दीर्घ)lp->rx_ring,(u_दीर्घ)lp->tx_ring);
	prपूर्णांकk("Descriptor addresses:\nRX: ");
	क्रम (i=0;i<lp->rxRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		prपूर्णांकk("0x%8.8lx  ",(u_दीर्घ)&lp->rx_ring[i].status);
	    पूर्ण
	पूर्ण
	prपूर्णांकk("...0x%8.8lx\n",(u_दीर्घ)&lp->rx_ring[i].status);
	prपूर्णांकk("TX: ");
	क्रम (i=0;i<lp->txRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		prपूर्णांकk("0x%8.8lx  ", (u_दीर्घ)&lp->tx_ring[i].status);
	    पूर्ण
	पूर्ण
	prपूर्णांकk("...0x%8.8lx\n", (u_दीर्घ)&lp->tx_ring[i].status);
	prपूर्णांकk("Descriptor buffers:\nRX: ");
	क्रम (i=0;i<lp->rxRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		prपूर्णांकk("0x%8.8x  ",le32_to_cpu(lp->rx_ring[i].buf));
	    पूर्ण
	पूर्ण
	prपूर्णांकk("...0x%8.8x\n",le32_to_cpu(lp->rx_ring[i].buf));
	prपूर्णांकk("TX: ");
	क्रम (i=0;i<lp->txRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		prपूर्णांकk("0x%8.8x  ", le32_to_cpu(lp->tx_ring[i].buf));
	    पूर्ण
	पूर्ण
	prपूर्णांकk("...0x%8.8x\n", le32_to_cpu(lp->tx_ring[i].buf));
	prपूर्णांकk("Ring size:\nRX: %d\nTX: %d\n",
	       (लघु)lp->rxRingSize,
	       (लघु)lp->txRingSize);
    पूर्ण
पूर्ण

अटल व्योम
de4x5_dbg_mii(काष्ठा net_device *dev, पूर्णांक k)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    u_दीर्घ iobase = dev->base_addr;

    अगर (de4x5_debug & DEBUG_MII) अणु
	prपूर्णांकk("\nMII device address: %d\n", lp->phy[k].addr);
	prपूर्णांकk("MII CR:  %x\n",mii_rd(MII_CR,lp->phy[k].addr,DE4X5_MII));
	prपूर्णांकk("MII SR:  %x\n",mii_rd(MII_SR,lp->phy[k].addr,DE4X5_MII));
	prपूर्णांकk("MII ID0: %x\n",mii_rd(MII_ID0,lp->phy[k].addr,DE4X5_MII));
	prपूर्णांकk("MII ID1: %x\n",mii_rd(MII_ID1,lp->phy[k].addr,DE4X5_MII));
	अगर (lp->phy[k].id != BROADCOM_T4) अणु
	    prपूर्णांकk("MII ANA: %x\n",mii_rd(0x04,lp->phy[k].addr,DE4X5_MII));
	    prपूर्णांकk("MII ANC: %x\n",mii_rd(0x05,lp->phy[k].addr,DE4X5_MII));
	पूर्ण
	prपूर्णांकk("MII 16:  %x\n",mii_rd(0x10,lp->phy[k].addr,DE4X5_MII));
	अगर (lp->phy[k].id != BROADCOM_T4) अणु
	    prपूर्णांकk("MII 17:  %x\n",mii_rd(0x11,lp->phy[k].addr,DE4X5_MII));
	    prपूर्णांकk("MII 18:  %x\n",mii_rd(0x12,lp->phy[k].addr,DE4X5_MII));
	पूर्ण अन्यथा अणु
	    prपूर्णांकk("MII 20:  %x\n",mii_rd(0x14,lp->phy[k].addr,DE4X5_MII));
	पूर्ण
    पूर्ण
पूर्ण

अटल व्योम
de4x5_dbg_media(काष्ठा net_device *dev)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);

    अगर (lp->media != lp->c_media) अणु
	अगर (de4x5_debug & DEBUG_MEDIA) अणु
	    prपूर्णांकk("%s: media is %s%s\n", dev->name,
		   (lp->media == NC  ? "unconnected, link down or incompatible connection" :
		    (lp->media == TP  ? "TP" :
		     (lp->media == ANS ? "TP/Nway" :
		      (lp->media == BNC ? "BNC" :
		       (lp->media == AUI ? "AUI" :
			(lp->media == BNC_AUI ? "BNC/AUI" :
			 (lp->media == EXT_SIA ? "EXT SIA" :
			  (lp->media == _100Mb  ? "100Mb/s" :
			   (lp->media == _10Mb   ? "10Mb/s" :
			    "???"
			    ))))))))), (lp->fdx?" full duplex.":"."));
	पूर्ण
	lp->c_media = lp->media;
    पूर्ण
पूर्ण

अटल व्योम
de4x5_dbg_srom(काष्ठा de4x5_srom *p)
अणु
    पूर्णांक i;

    अगर (de4x5_debug & DEBUG_SROM) अणु
	prपूर्णांकk("Sub-system Vendor ID: %04x\n", *((u_लघु *)p->sub_venकरोr_id));
	prपूर्णांकk("Sub-system ID:        %04x\n", *((u_लघु *)p->sub_प्रणाली_id));
	prपूर्णांकk("ID Block CRC:         %02x\n", (u_अक्षर)(p->id_block_crc));
	prपूर्णांकk("SROM version:         %02x\n", (u_अक्षर)(p->version));
	prपूर्णांकk("# controllers:        %02x\n", (u_अक्षर)(p->num_controllers));

	prपूर्णांकk("Hardware Address:     %pM\n", p->ieee_addr);
	prपूर्णांकk("CRC checksum:         %04x\n", (u_लघु)(p->chksum));
	क्रम (i=0; i<64; i++) अणु
	    prपूर्णांकk("%3d %04x\n", i<<1, (u_लघु)*((u_लघु *)p+i));
	पूर्ण
    पूर्ण
पूर्ण

अटल व्योम
de4x5_dbg_rx(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
    पूर्णांक i, j;

    अगर (de4x5_debug & DEBUG_RX) अणु
	prपूर्णांकk("R: %pM <- %pM len/SAP:%02x%02x [%d]\n",
	       skb->data, &skb->data[6],
	       (u_अक्षर)skb->data[12],
	       (u_अक्षर)skb->data[13],
	       len);
	क्रम (j=0; len>0;j+=16, len-=16) अणु
	  prपूर्णांकk("    %03x: ",j);
	  क्रम (i=0; i<16 && i<len; i++) अणु
	    prपूर्णांकk("%02x ",(u_अक्षर)skb->data[i+j]);
	  पूर्ण
	  prपूर्णांकk("\n");
	पूर्ण
    पूर्ण
पूर्ण

/*
** Perक्रमm IOCTL call functions here. Some are privileged operations and the
** effective uid is checked in those हालs. In the normal course of events
** this function is only used क्रम my testing.
*/
अटल पूर्णांक
de4x5_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
    काष्ठा de4x5_निजी *lp = netdev_priv(dev);
    काष्ठा de4x5_ioctl *ioc = (काष्ठा de4x5_ioctl *) &rq->अगरr_अगरru;
    u_दीर्घ iobase = dev->base_addr;
    पूर्णांक i, j, status = 0;
    s32 omr;
    जोड़ अणु
	u8  addr[144];
	u16 sval[72];
	u32 lval[36];
    पूर्ण पंचांगp;
    u_दीर्घ flags = 0;

    चयन(ioc->cmd) अणु
    हाल DE4X5_GET_HWADDR:           /* Get the hardware address */
	ioc->len = ETH_ALEN;
	क्रम (i=0; i<ETH_ALEN; i++) अणु
	    पंचांगp.addr[i] = dev->dev_addr[i];
	पूर्ण
	अगर (copy_to_user(ioc->data, पंचांगp.addr, ioc->len)) वापस -EFAULT;
	अवरोध;

    हाल DE4X5_SET_HWADDR:           /* Set the hardware address */
	अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
	अगर (copy_from_user(पंचांगp.addr, ioc->data, ETH_ALEN)) वापस -EFAULT;
	अगर (netअगर_queue_stopped(dev))
		वापस -EBUSY;
	netअगर_stop_queue(dev);
	क्रम (i=0; i<ETH_ALEN; i++) अणु
	    dev->dev_addr[i] = पंचांगp.addr[i];
	पूर्ण
	build_setup_frame(dev, PHYS_ADDR_ONLY);
	/* Set up the descriptor and give ownership to the card */
	load_packet(dev, lp->setup_frame, TD_IC | PERFECT_F | TD_SET |
		                                       SETUP_FRAME_LEN, (काष्ठा sk_buff *)1);
	lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;
	outl(POLL_DEMAND, DE4X5_TPD);                /* Start the TX */
	netअगर_wake_queue(dev);                      /* Unlock the TX ring */
	अवरोध;

    हाल DE4X5_SAY_BOO:              /* Say "Boo!" to the kernel log file */
	अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
	prपूर्णांकk("%s: Boo!\n", dev->name);
	अवरोध;

    हाल DE4X5_MCA_EN:               /* Enable pass all multicast addressing */
	अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
	omr = inl(DE4X5_OMR);
	omr |= OMR_PM;
	outl(omr, DE4X5_OMR);
	अवरोध;

    हाल DE4X5_GET_STATS:            /* Get the driver statistics */
    अणु
        काष्ठा pkt_stats statbuf;
	ioc->len = माप(statbuf);
	spin_lock_irqsave(&lp->lock, flags);
	स_नकल(&statbuf, &lp->pktStats, ioc->len);
	spin_unlock_irqrestore(&lp->lock, flags);
	अगर (copy_to_user(ioc->data, &statbuf, ioc->len))
		वापस -EFAULT;
	अवरोध;
    पूर्ण
    हाल DE4X5_CLR_STATS:            /* Zero out the driver statistics */
	अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
	spin_lock_irqsave(&lp->lock, flags);
	स_रखो(&lp->pktStats, 0, माप(lp->pktStats));
	spin_unlock_irqrestore(&lp->lock, flags);
	अवरोध;

    हाल DE4X5_GET_OMR:              /* Get the OMR Register contents */
	पंचांगp.addr[0] = inl(DE4X5_OMR);
	अगर (copy_to_user(ioc->data, पंचांगp.addr, 1)) वापस -EFAULT;
	अवरोध;

    हाल DE4X5_SET_OMR:              /* Set the OMR Register contents */
	अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
	अगर (copy_from_user(पंचांगp.addr, ioc->data, 1)) वापस -EFAULT;
	outl(पंचांगp.addr[0], DE4X5_OMR);
	अवरोध;

    हाल DE4X5_GET_REG:              /* Get the DE4X5 Registers */
	j = 0;
	पंचांगp.lval[0] = inl(DE4X5_STS); j+=4;
	पंचांगp.lval[1] = inl(DE4X5_BMR); j+=4;
	पंचांगp.lval[2] = inl(DE4X5_IMR); j+=4;
	पंचांगp.lval[3] = inl(DE4X5_OMR); j+=4;
	पंचांगp.lval[4] = inl(DE4X5_SISR); j+=4;
	पंचांगp.lval[5] = inl(DE4X5_SICR); j+=4;
	पंचांगp.lval[6] = inl(DE4X5_STRR); j+=4;
	पंचांगp.lval[7] = inl(DE4X5_SIGR); j+=4;
	ioc->len = j;
	अगर (copy_to_user(ioc->data, पंचांगp.lval, ioc->len))
		वापस -EFAULT;
	अवरोध;

#घोषणा DE4X5_DUMP              0x0f /* Dump the DE4X5 Status */
/*
      हाल DE4X5_DUMP:
	j = 0;
	पंचांगp.addr[j++] = dev->irq;
	क्रम (i=0; i<ETH_ALEN; i++) अणु
	    पंचांगp.addr[j++] = dev->dev_addr[i];
	पूर्ण
	पंचांगp.addr[j++] = lp->rxRingSize;
	पंचांगp.lval[j>>2] = (दीर्घ)lp->rx_ring; j+=4;
	पंचांगp.lval[j>>2] = (दीर्घ)lp->tx_ring; j+=4;

	क्रम (i=0;i<lp->rxRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		पंचांगp.lval[j>>2] = (दीर्घ)&lp->rx_ring[i].status; j+=4;
	    पूर्ण
	पूर्ण
	पंचांगp.lval[j>>2] = (दीर्घ)&lp->rx_ring[i].status; j+=4;
	क्रम (i=0;i<lp->txRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		पंचांगp.lval[j>>2] = (दीर्घ)&lp->tx_ring[i].status; j+=4;
	    पूर्ण
	पूर्ण
	पंचांगp.lval[j>>2] = (दीर्घ)&lp->tx_ring[i].status; j+=4;

	क्रम (i=0;i<lp->rxRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		पंचांगp.lval[j>>2] = (s32)le32_to_cpu(lp->rx_ring[i].buf); j+=4;
	    पूर्ण
	पूर्ण
	पंचांगp.lval[j>>2] = (s32)le32_to_cpu(lp->rx_ring[i].buf); j+=4;
	क्रम (i=0;i<lp->txRingSize-1;i++)अणु
	    अगर (i < 3) अणु
		पंचांगp.lval[j>>2] = (s32)le32_to_cpu(lp->tx_ring[i].buf); j+=4;
	    पूर्ण
	पूर्ण
	पंचांगp.lval[j>>2] = (s32)le32_to_cpu(lp->tx_ring[i].buf); j+=4;

	क्रम (i=0;i<lp->rxRingSize;i++)अणु
	    पंचांगp.lval[j>>2] = le32_to_cpu(lp->rx_ring[i].status); j+=4;
	पूर्ण
	क्रम (i=0;i<lp->txRingSize;i++)अणु
	    पंचांगp.lval[j>>2] = le32_to_cpu(lp->tx_ring[i].status); j+=4;
	पूर्ण

	पंचांगp.lval[j>>2] = inl(DE4X5_BMR);  j+=4;
	पंचांगp.lval[j>>2] = inl(DE4X5_TPD);  j+=4;
	पंचांगp.lval[j>>2] = inl(DE4X5_RPD);  j+=4;
	पंचांगp.lval[j>>2] = inl(DE4X5_RRBA); j+=4;
	पंचांगp.lval[j>>2] = inl(DE4X5_TRBA); j+=4;
	पंचांगp.lval[j>>2] = inl(DE4X5_STS);  j+=4;
	पंचांगp.lval[j>>2] = inl(DE4X5_OMR);  j+=4;
	पंचांगp.lval[j>>2] = inl(DE4X5_IMR);  j+=4;
	पंचांगp.lval[j>>2] = lp->chipset; j+=4;
	अगर (lp->chipset == DC21140) अणु
	    पंचांगp.lval[j>>2] = gep_rd(dev);  j+=4;
	पूर्ण अन्यथा अणु
	    पंचांगp.lval[j>>2] = inl(DE4X5_SISR); j+=4;
	    पंचांगp.lval[j>>2] = inl(DE4X5_SICR); j+=4;
	    पंचांगp.lval[j>>2] = inl(DE4X5_STRR); j+=4;
	    पंचांगp.lval[j>>2] = inl(DE4X5_SIGR); j+=4;
	पूर्ण
	पंचांगp.lval[j>>2] = lp->phy[lp->active].id; j+=4;
	अगर (lp->phy[lp->active].id && (!lp->useSROM || lp->useMII)) अणु
	    पंचांगp.lval[j>>2] = lp->active; j+=4;
	    पंचांगp.lval[j>>2]=mii_rd(MII_CR,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    पंचांगp.lval[j>>2]=mii_rd(MII_SR,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    पंचांगp.lval[j>>2]=mii_rd(MII_ID0,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    पंचांगp.lval[j>>2]=mii_rd(MII_ID1,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    अगर (lp->phy[lp->active].id != BROADCOM_T4) अणु
		पंचांगp.lval[j>>2]=mii_rd(MII_ANA,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
		पंचांगp.lval[j>>2]=mii_rd(MII_ANLPA,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    पूर्ण
	    पंचांगp.lval[j>>2]=mii_rd(0x10,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    अगर (lp->phy[lp->active].id != BROADCOM_T4) अणु
		पंचांगp.lval[j>>2]=mii_rd(0x11,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
		पंचांगp.lval[j>>2]=mii_rd(0x12,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    पूर्ण अन्यथा अणु
		पंचांगp.lval[j>>2]=mii_rd(0x14,lp->phy[lp->active].addr,DE4X5_MII); j+=4;
	    पूर्ण
	पूर्ण

	पंचांगp.addr[j++] = lp->txRingSize;
	पंचांगp.addr[j++] = netअगर_queue_stopped(dev);

	ioc->len = j;
	अगर (copy_to_user(ioc->data, पंचांगp.addr, ioc->len)) वापस -EFAULT;
	अवरोध;

*/
    शेष:
	वापस -EOPNOTSUPP;
    पूर्ण

    वापस status;
पूर्ण

अटल पूर्णांक __init de4x5_module_init (व्योम)
अणु
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_PCI
	err = pci_रेजिस्टर_driver(&de4x5_pci_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_EISA
	err |= eisa_driver_रेजिस्टर (&de4x5_eisa_driver);
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल व्योम __निकास de4x5_module_निकास (व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver (&de4x5_pci_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_EISA
	eisa_driver_unरेजिस्टर (&de4x5_eisa_driver);
#पूर्ण_अगर
पूर्ण

module_init (de4x5_module_init);
module_निकास (de4x5_module_निकास);
