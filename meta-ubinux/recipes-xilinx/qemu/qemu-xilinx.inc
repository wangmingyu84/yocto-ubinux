SUMMARY = "Xilinx's fork of a fast open source processor emulator"
HOMEPAGE = "https://github.com/xilinx/qemu/"

# x86_64 is needed to build nativesdks
QEMU_TARGETS = "aarch64 arm microblaze microblazeel x86_64 i386"

LIC_FILES_CHKSUM = " \
		file://COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac \
		file://COPYING.LIB;endline=24;md5=8c5efda6cf1e1b03dcfd0e6c0d271c7f \
		"
DEPENDS = "glib-2.0 zlib pixman"
XILINX_RELEASE_VERSION = "v2021.1"
XILINX_QEMU_VERSION ?= "v5.1.0"
BRANCH ?= "branch/xilinx-v2021.1"
SRCREV = "e40b634b24b37fe521bb2857c5e93ee1d30c2e37"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

PV = "${XILINX_QEMU_VERSION}-xilinx-${XILINX_RELEASE_VERSION}+git${SRCPV}"
REPO ?= "gitsm://github.com/Xilinx/qemu.git;protocol=https"

BRANCHARG = "${@['nobranch=1', 'branch=${BRANCH}'][d.getVar('BRANCH', True) != '']}"
SRC_URI = "${REPO};${BRANCHARG}"

SRC_URI:append = " file://0010-configure-Add-pkg-config-handling-for-libgcrypt.patch \
		   file://0001-Add-enable-disable-udev.patch \
"

S = "${WORKDIR}/git"

# Disable KVM completely
PACKAGECONFIG:remove = "kvm"
PACKAGECONFIG:append = " fdt gcrypt"

DISABLE_STATIC:pn-${PN} = ""

PTEST_ENABLED = ""

EXTRA_OECONF:append = " --with-git=/bin/false --disable-git-update"
EXTRA_OECONF:remove = " --with-suffix=${BPN} --with-git-submodules=ignore --meson=meson"

do_install:append() {
	# Prevent QA warnings about installed ${localstatedir}/run
	if [ -d ${D}${localstatedir}/run ]; then rmdir ${D}${localstatedir}/run; fi
}

FILES:${PN} += "${datadir}/qemu"
