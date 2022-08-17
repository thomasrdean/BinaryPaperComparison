template_file=$1

base_file="${template_file%.*}"
cpp_file="${base_file}".cpp
obj_file="${base_file}".o
generated_file="${base_file}".gen
generated_file2="${base_file}".gen2
decisions_file="${base_file}".dec

echo "Cleaning:"
rm "${base_file}" "${cpp_file}" "${obj_file}" "${generated_file}" "${generated_file2}" "${decisions_file}"

echo "Compiling:"
orig_dir=$(pwd)
ff_dir="${orig_dir}/FormatFuzzer-master"
cd "${ff_dir}"
./ffcompile "${orig_dir}/${template_file}" "${cpp_file}"
g++ -c -I . -std=c++17 -g -O3 -Wall fuzzer.cpp
g++ -c -I . -std=c++17 -g -O3 -Wall "${cpp_file}"
g++ -O3 -g "${obj_file}" fuzzer.o -o "${orig_dir}/${base_file}" -lz
cd "${orig_dir}"

echo "Executing:"
./"${base_file}" fuzz "${generated_file}"

./"${base_file}" parse --decisions "${decisions_file}" "${generated_file}"

./"${base_file}" fuzz --decisions "${decisions_file}" "${generated_file2}"

echo "Comparison:"
diff -s "${generated_file}" "${generated_file2}"
