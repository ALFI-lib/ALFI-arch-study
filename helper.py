#!/usr/bin/env python3

import argparse
import subprocess
from pathlib import Path


ARCHITECTURES = {
	'x86_64': {
		'gcc': {
			'compiler': 'x86_64-linux-gnu-g++',
			'objdump': 'x86_64-linux-gnu-objdump',
		},
		'clang': {
			'compiler': 'clang++',
			'objdump': 'llvm-objdump',
		},
	},
	'rv64gv': {
		'gcc': {
			'compiler': 'riscv64-linux-gnu-g++',
			'objdump': 'riscv64-linux-gnu-objdump',
		},
		'clang': {
			'compiler': 'clang++',
			'objdump': 'llvm-objdump',
		},
	},
}

PROFILES = [
	'O0',
	'O2',
	'O3',
	'Ofast',
]

OPENMP_OPTIONS = [
	False,
	True,
]

COMPILERS = [
	'gcc',
	'clang',
]

TARGETS = [
	'alfi',
	'barycentric',
	'hermite',
]


def run(command):
	print(' '.join(command), flush=True)
	subprocess.check_call(command)


def build(arch, compiler, profile, openmp, target):
	config_name = f'{arch}-{compiler}-{profile}'

	if openmp:
		config_name += '-openmp'

	build_dir = Path('build') / config_name

	toolchain = ARCHITECTURES[arch][compiler]

	run([
		'cmake',
		'-S', '.',
		'-B', str(build_dir),
		f'-DCMAKE_CXX_COMPILER={toolchain["compiler"]}',
		f'-DCMAKE_OBJDUMP={toolchain["objdump"]}',
		f'-DALFI_ARCH={arch}',
		f'-DALFI_COMPILER={compiler}',
		f'-DALFI_PROFILE={profile}',
		f'-DALFI_OPENMP={"ON" if openmp else "OFF"}',
	])

	run([
		'cmake',
		'--build',
		str(build_dir),
		'--target', target,
		'-j',
	])


parser = argparse.ArgumentParser()

parser.add_argument(
	'--arch',
	choices=[*ARCHITECTURES, 'all'],
	default='all',
)

parser.add_argument(
	'--compiler',
	choices=[*COMPILERS, 'all'],
	default='all',
)

parser.add_argument(
	'--profile',
	choices=[*PROFILES, 'all'],
	default='all',
)

parser.add_argument(
	'--openmp',
	choices=['on', 'off', 'both'],
	default='both',
)

parser.add_argument(
	'--target',
	choices=[*TARGETS, 'all'],
	default='all',
)

args = parser.parse_args()


architectures = list(ARCHITECTURES) if args.arch == 'all' else [args.arch]
compilers = COMPILERS if args.compiler == 'all' else [args.compiler]
profiles = PROFILES if args.profile == 'all' else [args.profile]
openmp_options = OPENMP_OPTIONS if args.openmp == 'both' else [args.openmp == 'on']
targets = TARGETS if args.target == 'all' else [args.target]


for arch in architectures:
	for compiler in compilers:
		for profile in profiles:
			for openmp in openmp_options:
				for target in targets:
					build(arch, compiler, profile, openmp, target)