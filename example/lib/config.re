let home = {
  let env_var =
    switch (Sys.os_type) {
    | "Unix" => "HOME"
    | _ => "APPDATA"
    };
  Sys.getenv_opt(env_var)
  |> Option.to_result(~none=Error.missing_env(env_var));
};

let default_cache_dir =
  Result.map(
    home => "demo" |> Filename.concat(".cache") |> Filename.concat(home),
    home,
  );

let default_config_dir =
  Result.map(
    home => "demo" |> Filename.concat(".config") |> Filename.concat(home),
    home,
  );

let cache_dir =
  Sys.getenv_opt("DEMO_CACHE_DIR")
  |> Option.map(Result.ok)
  |> Option.value(~default=default_cache_dir);

let config_dir =
  Sys.getenv_opt("DEMO_CONFIG_DIR")
  |> Option.map(Result.ok)
  |> Option.value(~default=default_config_dir);
